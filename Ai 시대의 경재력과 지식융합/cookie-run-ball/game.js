const canvas = document.querySelector("#gameCanvas");
const ctx = canvas.getContext("2d");

const distanceText = document.querySelector("#distanceText");
const scoreText = document.querySelector("#scoreText");
const healthText = document.querySelector("#healthText");
const bestText = document.querySelector("#bestText");
const walletText = document.querySelector("#walletText");
const mainMenu = document.querySelector("#mainMenu");
const playButton = document.querySelector("#playButton");
const menuMoneyText = document.querySelector("#menuMoneyText");
const upgradeList = document.querySelector("#upgradeList");
const overlay = document.querySelector("#overlay");
const overlayStatus = document.querySelector("#overlayStatus");
const overlayTitle = document.querySelector("#overlayTitle");
const overlayText = document.querySelector("#overlayText");
const startButton = document.querySelector("#startButton");
const menuButton = document.querySelector("#menuButton");

const W = canvas.width;
const H = canvas.height;
const groundY = 440;
const gravity = 0.82;
const jumpVelocity = -15.1;
const doubleJumpVelocity = -12.6;
const maxFallSpeed = 18;
const baseMaxHealth = 100;
const pitDamage = 50;
const energyDrainPerFrame = 0.032;
const slideKeys = ["ArrowDown", "KeyS", "ShiftLeft", "ShiftRight"];

const upgradeDefs = {
  health: {
    title: "튼튼한 반죽",
    detail: "시작 체력과 물약 회복량 증가",
    max: 5,
    baseCost: 90,
    costStep: 80,
  },
  jumps: {
    title: "스프링 젤리 신발",
    detail: "공중 점프 횟수 증가",
    max: 2,
    baseCost: 180,
    costStep: 220,
  },
  jelly: {
    title: "젤리 상인 수첩",
    detail: "젤리 1개당 획득 코인 증가",
    max: 5,
    baseCost: 120,
    costStep: 110,
  },
};

const economy = {
  wallet: Number(localStorage.getItem("rollingDashWallet") || 0),
  upgrades: loadUpgrades(),
};

const state = {
  mode: "menu",
  time: 0,
  speed: 5.4,
  distance: 0,
  score: 0,
  best: Number(localStorage.getItem("rollingDashBest") || 0),
  spawnTimer: 0,
  potionTimer: 0,
  obstacles: [],
  platforms: [],
  jellies: [],
  potions: [],
  particles: [],
  keys: new Set(),
  lastFrame: 0,
};

const player = {
  x: 150,
  y: groundY - 30,
  r: 30,
  vy: 0,
  health: getMaxHealth(),
  grounded: true,
  jumpsLeft: 2,
  maxJumps: getMaxJumps(),
  jumpHold: 0,
  runPhase: 0,
  doubleJumpPulse: 0,
  hurtTimer: 0,
  sliding: false,
  slideDustTimer: 0,
};

bestText.textContent = String(state.best);
if (walletText) walletText.textContent = String(economy.wallet);

const obstacleTypes = {
  spike: { type: "spike", width: 44, height: 48, damage: 28, color: "#e14f4f" },
  doubleSpike: { type: "double-spike", width: 92, height: 52, damage: 32, color: "#e14f4f" },
  wall: { type: "wall", variant: "wafer", width: 42, height: 92, damage: 22, color: "#806452" },
  tallWall: { type: "wall", variant: "oven", width: 56, height: 148, damage: 30, color: "#574a42" },
  crumbBlock: { type: "crumb", width: 64, height: 70, damage: 24, color: "#b77a45" },
  flamePillar: { type: "flame", width: 48, height: 112, damage: 30, color: "#f26b3f" },
  flyingFork: { type: "flying", width: 108, height: 34, y: groundY - 116, damage: 24, color: "#dde4e6" },
  pit: { type: "pit", width: 130, height: 0, damage: 32, color: "#151820" },
  widePit: { type: "pit", width: 245, height: 0, damage: 38, color: "#151820" },
  hangingTray: { type: "hanging", width: 132, height: 68, y: groundY - 140, damage: 24, color: "#b75a45" },
  lowFlame: { type: "hanging", width: 96, height: 76, y: groundY - 148, damage: 26, color: "#e06b3d" },
};

function loadUpgrades() {
  try {
    const saved = JSON.parse(localStorage.getItem("rollingDashUpgrades") || "{}");
    return {
      health: clampUpgrade(saved.health, "health"),
      jumps: clampUpgrade(saved.jumps, "jumps"),
      jelly: clampUpgrade(saved.jelly, "jelly"),
    };
  } catch {
    return { health: 0, jumps: 0, jelly: 0 };
  }
}

function clampUpgrade(value, key) {
  const level = Number.isFinite(Number(value)) ? Number(value) : 0;
  return Math.max(0, Math.min(upgradeDefs[key].max, Math.floor(level)));
}

function saveEconomy() {
  localStorage.setItem("rollingDashWallet", String(economy.wallet));
  localStorage.setItem("rollingDashUpgrades", JSON.stringify(economy.upgrades));
}

function getMaxHealth() {
  return baseMaxHealth + economy.upgrades.health * 24;
}

function getMaxJumps() {
  return 2 + economy.upgrades.jumps;
}

function getJellyValue() {
  return 5 + economy.upgrades.jelly * 3;
}

function getPotionHeal() {
  return 28 + economy.upgrades.health * 5;
}

function getUpgradeCost(key) {
  const def = upgradeDefs[key];
  const level = economy.upgrades[key];
  return def.baseCost + level * def.costStep + level * level * 35;
}

function renderMenu() {
  if (menuMoneyText) menuMoneyText.textContent = String(economy.wallet);
  if (walletText) walletText.textContent = String(economy.wallet);
  if (!upgradeList) return;

  upgradeList.innerHTML = Object.entries(upgradeDefs)
    .map(([key, def]) => {
      const level = economy.upgrades[key];
      const maxed = level >= def.max;
      const cost = getUpgradeCost(key);
      const disabled = maxed || economy.wallet < cost ? "disabled" : "";
      const valueText =
        key === "health"
          ? `최대 체력 ${getMaxHealth()}`
          : key === "jumps"
            ? `최대 점프 ${getMaxJumps()}회`
            : `젤리당 ${getJellyValue()}코인`;
      const buttonText = maxed ? "최대" : `${cost} 코인`;
      return `
        <article class="upgrade-card">
          <div>
            <p class="upgrade-level">Lv. ${level}/${def.max}</p>
            <h3>${def.title}</h3>
            <p>${def.detail}</p>
            <strong>${valueText}</strong>
          </div>
          <button class="upgrade-button" type="button" data-upgrade="${key}" ${disabled}>${buttonText}</button>
        </article>
      `;
    })
    .join("");

  if (typeof document.querySelectorAll === "function") {
    document.querySelectorAll("[data-upgrade]").forEach((button) => {
      button.addEventListener("click", () => buyUpgrade(button.dataset.upgrade));
    });
  }
}

function buyUpgrade(key) {
  const def = upgradeDefs[key];
  if (!def || economy.upgrades[key] >= def.max) return;

  const cost = getUpgradeCost(key);
  if (economy.wallet < cost) return;

  economy.wallet -= cost;
  economy.upgrades[key] += 1;
  player.maxJumps = getMaxJumps();
  saveEconomy();
  renderMenu();
  updateStats();
}

function showMenu() {
  state.mode = "menu";
  state.keys.clear();
  overlay.classList.add("hidden");
  if (mainMenu) mainMenu.classList.remove("hidden");
  renderMenu();
  draw();
}

function startRun() {
  if (mainMenu) mainMenu.classList.add("hidden");
  resetGame();
  requestAnimationFrame(loop);
}

function resetGame() {
  state.mode = "running";
  state.time = 0;
  state.speed = 5.4;
  state.distance = 0;
  state.score = 0;
  state.spawnTimer = 28;
  state.potionTimer = 360;
  state.obstacles = [];
  state.platforms = [];
  state.jellies = [];
  state.potions = [];
  state.particles = [];
  state.lastFrame = performance.now();

  player.x = 150;
  player.y = groundY - player.r;
  player.vy = 0;
  player.maxJumps = getMaxJumps();
  player.health = getMaxHealth();
  player.grounded = true;
  player.jumpsLeft = player.maxJumps;
  player.jumpHold = 0;
  player.runPhase = 0;
  player.doubleJumpPulse = 0;
  player.hurtTimer = 0;
  player.sliding = false;
  player.slideDustTimer = 0;

  overlay.classList.add("hidden");
  updateStats();
}

function endGame(reason) {
  state.mode = "gameover";
  state.best = Math.max(state.best, state.score);
  localStorage.setItem("rollingDashBest", String(state.best));
  bestText.textContent = String(state.best);

  overlayTitle.textContent = "기록 종료";
  overlayText.textContent = `${reason} 최종 거리 ${Math.floor(state.distance)}m, 이번에 모은 코인 ${state.score}개입니다.`;
  startButton.textContent = "다시 뛰기";
  if (menuButton) menuButton.classList.remove("hidden");
  overlayStatus.textContent = "GAME OVER";
  overlay.classList.remove("hidden");
  renderMenu();
}

function pauseGame() {
  if (state.mode === "running") {
    state.mode = "paused";
    overlayTitle.textContent = "일시정지";
    overlayText.textContent = "P 키를 다시 누르거나 버튼을 눌러 계속합니다.";
    startButton.textContent = "계속";
    if (menuButton) menuButton.classList.add("hidden");
    overlayStatus.textContent = "PAUSED";
    overlay.classList.remove("hidden");
  } else if (state.mode === "paused") {
    state.mode = "running";
    state.lastFrame = performance.now();
    overlay.classList.add("hidden");
  }
}

function updateStats() {
  distanceText.textContent = `${Math.floor(state.distance)}m`;
  scoreText.textContent = String(state.score);
  healthText.textContent = String(Math.max(0, Math.ceil(player.health)));
  if (walletText) walletText.textContent = String(economy.wallet);
  if (menuMoneyText) menuMoneyText.textContent = String(economy.wallet);
}

function jump() {
  if (state.mode !== "running" || player.jumpsLeft <= 0) return;
  player.sliding = false;

  if (player.grounded) {
    player.vy = jumpVelocity;
    player.jumpHold = 9;
    spawnDust(player.x - 12, player.y + player.r, 10, "#f8f4e8");
  } else {
    player.vy = doubleJumpVelocity;
    player.jumpHold = 6;
    player.doubleJumpPulse = 18;
    spawnDust(player.x, player.y + 4, 18, "#91d4f2");
  }

  player.grounded = false;
  player.jumpsLeft -= 1;
}

function resetJumps() {
  player.grounded = true;
  player.jumpsLeft = player.maxJumps;
  player.jumpHold = 0;
}

function wantsToSlide() {
  return slideKeys.some((code) => state.keys.has(code));
}

function takeDamage(amount, reason) {
  if (player.hurtTimer > 0 || state.mode !== "running") return;

  player.health = Math.max(0, player.health - amount);
  player.hurtTimer = 78;
  player.vy = Math.min(player.vy, -8.2);
  player.grounded = false;
  player.jumpsLeft = Math.max(1, player.jumpsLeft);
  spawnDust(player.x, player.y, 24, "#e14f4f");
  updateStats();

  if (player.health <= 0) {
    endGame(reason);
  }
}

function recoverFromPit() {
  player.y = groundY - player.r;
  player.vy = -9;
  resetJumps();
}

function spawnDust(x, y, count, color) {
  for (let i = 0; i < count; i += 1) {
    state.particles.push({
      x,
      y,
      vx: -Math.random() * 3.2 - 0.6,
      vy: -Math.random() * 3.5,
      life: 28 + Math.random() * 12,
      size: 3 + Math.random() * 5,
      color,
    });
  }
}

function addObstacle(blueprint, xOffset = 30) {
  state.obstacles.push({
    ...blueprint,
    x: W + xOffset,
    y: blueprint.y ?? (blueprint.type === "pit" ? groundY : groundY - blueprint.height),
    hit: false,
  });
}

function addPlatform(xOffset, y, width) {
  state.platforms.push({
    x: W + xOffset,
    y,
    width,
    height: 18,
  });
}

function addJelly(x, y, color = "#f87ed0") {
  state.jellies.push({
    x,
    y,
    r: 12,
    color,
    taken: false,
    wobble: Math.random() * Math.PI * 2,
  });
}

function addJellyLine(startOffset, y, count, spacing = 34, color = "#f87ed0") {
  for (let i = 0; i < count; i += 1) {
    addJelly(W + startOffset + i * spacing, y + Math.sin(i * 0.9) * 12, color);
  }
}

function addJellyArc(startOffset, baseY, count, spacing = 32, height = 42, color = "#f87ed0") {
  for (let i = 0; i < count; i += 1) {
    const t = count === 1 ? 0.5 : i / (count - 1);
    const y = baseY - Math.sin(t * Math.PI) * height;
    addJelly(W + startOffset + i * spacing, y, color);
  }
}

function addPotion(xOffset, y = groundY - 92) {
  state.potions.push({
    x: W + xOffset,
    y,
    r: 15,
    taken: false,
    wobble: Math.random() * Math.PI * 2,
  });
}

function addPotionCue(xOffset, y) {
  addJellyArc(xOffset - 82, y + 12, 4, 28, 22, "#7be0ff");
  addPotion(xOffset + 40, y);
}

function spawnScheduledPotion() {
  const high = Math.random() > 0.55;
  if (high) {
    addPotionCue(88, 300);
  } else {
    addPotionCue(86, groundY - 86);
  }
}

function createPattern() {
  const roll = Math.random();

  if (state.distance < 120) {
    addObstacle(obstacleTypes.spike, 40);
    addJellyArc(42, groundY - 96, 5, 30, 42, "#f87ed0");
    return;
  }

  if (roll < 0.12) {
    addObstacle(obstacleTypes.doubleSpike, 40);
    addJellyArc(38, groundY - 110, 6, 28, 44, "#7be0ff");
    return;
  }

  if (roll < 0.24) {
    addObstacle(obstacleTypes.crumbBlock, 52);
    addObstacle(obstacleTypes.spike, 130);
    addJellyArc(38, groundY - 132, 6, 28, 56, "#f8d34f");
    return;
  }

  if (roll < 0.36) {
    addObstacle(obstacleTypes.hangingTray, 68);
    addJellyLine(78, groundY - 58, 6, 29, "#f87ed0");
    return;
  }

  if (roll < 0.48) {
    addObstacle(obstacleTypes.flamePillar, 64);
    addJellyArc(54, groundY - 160, 7, 26, 50, "#f8d34f");
    return;
  }

  if (roll < 0.6) {
    addObstacle(obstacleTypes.flyingFork, 76);
    addObstacle(obstacleTypes.spike, 292);
    addJellyLine(84, groundY - 58, 5, 28, "#7be0ff");
    addJellyArc(292, groundY - 112, 4, 28, 38, "#f87ed0");
    return;
  }

  if (roll < 0.7) {
    addObstacle(obstacleTypes.pit, 50);
    addJellyArc(62, groundY - 116, 6, 28, 42, "#f87ed0");
    return;
  }

  if (roll < 0.8) {
    addObstacle(obstacleTypes.widePit, 44);
    addPlatform(104, 326, 118);
    addObstacle(obstacleTypes.hangingTray, 264);
    addJellyLine(118, 292, 5, 28, "#7be0ff");
    addPotion(306, 300);
    return;
  }

  if (roll < 0.9) {
    addPlatform(74, 318, 122);
    addObstacle(obstacleTypes.tallWall, 238);
    addObstacle(obstacleTypes.flamePillar, 330);
    addJellyLine(88, 284, 5, 28, "#f8d34f");
    addJellyArc(220, groundY - 190, 5, 26, 34, "#f87ed0");
    return;
  }

  addObstacle(obstacleTypes.spike, 36);
  addObstacle(obstacleTypes.lowFlame, 140);
  addObstacle(obstacleTypes.crumbBlock, 368);
  addPlatform(464, 306, 108);
  addJellyLine(148, groundY - 58, 4, 28, "#f87ed0");
  addJellyArc(390, groundY - 148, 5, 28, 38, "#f8d34f");
}

function update(dt) {
  if (state.mode !== "running") return;

  const scale = Math.min(dt / 16.67, 2);
  const previousBottom = player.y + player.r;

  state.time += dt;
  state.distance += state.speed * scale * 0.17;
  state.speed = Math.min(11.4, 5.4 + state.distance / 590);
  player.hurtTimer = Math.max(0, player.hurtTimer - scale);
  player.health = Math.max(0, player.health - energyDrainPerFrame * scale);
  if (player.health <= 0) {
    endGame("체력이 모두 소진되었습니다.");
    return;
  }

  if ((state.keys.has("Space") || state.keys.has("ArrowUp")) && player.jumpHold > 0) {
    player.vy -= 0.34 * scale;
    player.jumpHold -= scale;
  }

  player.vy = Math.min(maxFallSpeed, player.vy + gravity * scale);
  player.y += player.vy * scale;
  player.runPhase += state.speed * 0.08 * scale;
  player.doubleJumpPulse = Math.max(0, player.doubleJumpPulse - scale);

  const landingPlatform = findLandingPlatform(previousBottom);
  if (landingPlatform) {
    if (!player.grounded && player.vy > 2) {
      spawnDust(player.x - 8, landingPlatform.y, 7, "#dcefdc");
    }
    player.y = landingPlatform.y - player.r;
    player.vy = 0;
    resetJumps();
  } else {
    const onPit = isPlayerOverPit();
    if (!onPit && player.y + player.r >= groundY) {
      if (!player.grounded && player.vy > 2) {
        spawnDust(player.x - 8, groundY, 8, "#d4e6d6");
      }
      player.y = groundY - player.r;
      player.vy = 0;
      resetJumps();
    } else {
      player.grounded = false;
    }
  }

  if (player.y - player.r > H) {
    takeDamage(pitDamage, "체력이 모두 소진되었습니다.");
    if (state.mode === "running") recoverFromPit();
  }

  if (player.grounded && wantsToSlide() && player.hurtTimer <= 0) {
    if (!player.sliding) {
      spawnDust(player.x - 24, player.y + player.r - 4, 7, "#d9c59a");
    }
    player.sliding = true;
    player.jumpHold = 0;
    player.slideDustTimer -= scale;
    if (player.slideDustTimer <= 0) {
      spawnDust(player.x - 32, player.y + player.r - 5, 3, "#d9c59a");
      player.slideDustTimer = 7;
    }
  } else {
    player.sliding = false;
    player.slideDustTimer = 0;
  }

  state.spawnTimer -= scale;
  if (state.spawnTimer <= 0) {
    createPattern();
    const difficultyGap = Math.max(68, 118 - state.distance / 38);
    state.spawnTimer = difficultyGap + Math.random() * 34;
  }

  state.potionTimer -= scale;
  if (state.potionTimer <= 0) {
    spawnScheduledPotion();
    state.potionTimer = 560 + Math.random() * 180;
  }

  for (const obstacle of state.obstacles) {
    obstacle.x -= state.speed * scale;
  }
  for (const platform of state.platforms) {
    platform.x -= state.speed * scale;
  }
  for (const jelly of state.jellies) {
    jelly.x -= state.speed * scale;
    jelly.wobble += 0.08 * scale;
    if (!jelly.taken && circleHitsCircle(player.x, player.y, player.r, jelly.x, jelly.y, jelly.r + 4)) {
      jelly.taken = true;
      const coinValue = getJellyValue();
      state.score += coinValue;
      economy.wallet += coinValue;
      saveEconomy();
      spawnDust(jelly.x, jelly.y, 8, jelly.color);
      renderMenu();
      updateStats();
    }
  }
  for (const potion of state.potions) {
    potion.x -= state.speed * scale;
    potion.wobble += 0.07 * scale;
    if (!potion.taken && circleHitsCircle(player.x, player.y, player.r, potion.x, potion.y, potion.r + 6)) {
      potion.taken = true;
      player.health = Math.min(getMaxHealth(), player.health + getPotionHeal());
      spawnDust(potion.x, potion.y, 18, "#5fc778");
      updateStats();
    }
  }

  state.obstacles = state.obstacles.filter((obstacle) => obstacle.x + obstacle.width > -80);
  state.platforms = state.platforms.filter((platform) => platform.x + platform.width > -80);
  state.jellies = state.jellies.filter((jelly) => jelly.x + jelly.r > -40 && !jelly.taken);
  state.potions = state.potions.filter((potion) => potion.x + potion.r > -40 && !potion.taken);

  for (const particle of state.particles) {
    particle.x += particle.vx * scale;
    particle.y += particle.vy * scale;
    particle.vy += 0.14 * scale;
    particle.life -= scale;
  }
  state.particles = state.particles.filter((particle) => particle.life > 0);

  const hitObstacle = state.obstacles.find((obstacle) => !obstacle.hit && collidesWithPlayer(obstacle));
  if (hitObstacle) {
    hitObstacle.hit = true;
    takeDamage(hitObstacle.damage || 25, "체력이 모두 소진되었습니다.");
  }

  updateStats();
}

function findLandingPlatform(previousBottom) {
  if (player.vy < 0) return null;
  return state.platforms.find((platform) => {
    const withinX = player.x + player.r * 0.65 > platform.x && player.x - player.r * 0.65 < platform.x + platform.width;
    const crossedTop = previousBottom <= platform.y + 6 && player.y + player.r >= platform.y;
    return withinX && crossedTop;
  });
}

function isPlayerOverPit() {
  return state.obstacles.some((obstacle) => {
    if (obstacle.type !== "pit") return false;
    const left = obstacle.x + 12;
    const right = obstacle.x + obstacle.width - 12;
    return player.x + player.r * 0.45 > left && player.x - player.r * 0.45 < right;
  });
}

function collidesWithPlayer(obstacle) {
  if (obstacle.type === "pit") return false;
  const hitbox = getPlayerHitbox();

  if (obstacle.type === "spike" || obstacle.type === "double-spike") {
    const spikeCount = obstacle.type === "double-spike" ? 2 : 1;
    for (let i = 0; i < spikeCount; i += 1) {
      const width = obstacle.width / spikeCount;
      const left = obstacle.x + i * width + 5;
      const right = left + width - 10;
      const top = groundY - obstacle.height;
      const triangle = [
        { x: left, y: groundY },
        { x: (left + right) / 2, y: top },
        { x: right, y: groundY },
      ];
      if (rectHitsTriangle(hitbox, triangle)) return true;
    }
    return false;
  }

  return rectHitsRect(hitbox, {
    x: obstacle.x,
    y: obstacle.y,
    width: obstacle.width,
    height: obstacle.height,
  });
}

function getPlayerHitbox() {
  if (player.sliding) {
    return {
      x: player.x - 28,
      y: player.y - 26,
      width: 56,
      height: 56,
    };
  }

  return {
    x: player.x - 19,
    y: player.y - 68,
    width: 38,
    height: 88,
  };
}

function rectHitsRect(a, b) {
  return (
    a.x < b.x + b.width &&
    a.x + a.width > b.x &&
    a.y < b.y + b.height &&
    a.y + a.height > b.y
  );
}

function rectHitsTriangle(rect, triangle) {
  const rectPoints = [
    { x: rect.x, y: rect.y },
    { x: rect.x + rect.width, y: rect.y },
    { x: rect.x + rect.width, y: rect.y + rect.height },
    { x: rect.x, y: rect.y + rect.height },
  ];

  if (triangle.some((point) => pointInRect(point, rect))) return true;
  if (rectPoints.some((point) => pointInTriangle(point, triangle))) return true;

  const rectEdges = rectPoints.map((point, index) => [point, rectPoints[(index + 1) % rectPoints.length]]);
  const triangleEdges = triangle.map((point, index) => [point, triangle[(index + 1) % triangle.length]]);
  return triangleEdges.some(([a, b]) => rectEdges.some(([c, d]) => segmentsIntersect(a, b, c, d)));
}

function pointInRect(point, rect) {
  return (
    point.x >= rect.x &&
    point.x <= rect.x + rect.width &&
    point.y >= rect.y &&
    point.y <= rect.y + rect.height
  );
}

function segmentsIntersect(a, b, c, d) {
  const direction = (p, q, r) => (r.x - p.x) * (q.y - p.y) - (q.x - p.x) * (r.y - p.y);
  const d1 = direction(c, d, a);
  const d2 = direction(c, d, b);
  const d3 = direction(a, b, c);
  const d4 = direction(a, b, d);
  return ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0));
}

function circleHitsCircle(ax, ay, ar, bx, by, br) {
  const dx = ax - bx;
  const dy = ay - by;
  const radius = ar + br;
  return dx * dx + dy * dy < radius * radius;
}

function circleHitsTriangle(circle, triangle) {
  if (pointInTriangle({ x: circle.x, y: circle.y }, triangle)) return true;
  for (let i = 0; i < 3; i += 1) {
    const a = triangle[i];
    const b = triangle[(i + 1) % 3];
    if (distanceToSegment(circle, a, b) < circle.r) return true;
  }
  return false;
}

function pointInTriangle(point, triangle) {
  const [a, b, c] = triangle;
  const area = (p1, p2, p3) =>
    Math.abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2);
  const total = area(a, b, c);
  const split = area(point, b, c) + area(a, point, c) + area(a, b, point);
  return Math.abs(total - split) < 0.5;
}

function distanceToSegment(point, a, b) {
  const dx = b.x - a.x;
  const dy = b.y - a.y;
  const lengthSq = dx * dx + dy * dy;
  const t = lengthSq === 0 ? 0 : Math.max(0, Math.min(1, ((point.x - a.x) * dx + (point.y - a.y) * dy) / lengthSq));
  const px = a.x + t * dx;
  const py = a.y + t * dy;
  return Math.hypot(point.x - px, point.y - py);
}

function draw() {
  drawBackground();
  drawWorld();
  drawPlayer();

  if (state.mode === "running") {
    requestAnimationFrame(loop);
  }
}

function drawBackground() {
  const sky = ctx.createLinearGradient(0, 0, 0, H);
  sky.addColorStop(0, "#91d4f2");
  sky.addColorStop(0.62, "#f8f4e8");
  sky.addColorStop(1, "#d9e5c7");
  ctx.fillStyle = sky;
  ctx.fillRect(0, 0, W, H);

  ctx.fillStyle = "rgba(255,255,255,0.55)";
  for (let i = 0; i < 7; i += 1) {
    const x = ((i * 190 - state.distance * 0.8) % (W + 220)) - 110;
    drawCloud(x, 72 + (i % 3) * 42, 0.82 + (i % 2) * 0.18);
  }

  ctx.fillStyle = "#7fbf80";
  drawHill(-80 - (state.distance * 0.6) % 260, 408, 280, 82);
  drawHill(170 - (state.distance * 0.45) % 320, 392, 360, 112);
  drawHill(560 - (state.distance * 0.35) % 420, 406, 320, 86);
}

function drawCloud(x, y, s) {
  ctx.beginPath();
  ctx.arc(x, y, 22 * s, Math.PI * 0.5, Math.PI * 1.5);
  ctx.arc(x + 24 * s, y - 18 * s, 28 * s, Math.PI, Math.PI * 1.85);
  ctx.arc(x + 58 * s, y - 8 * s, 24 * s, Math.PI * 1.1, Math.PI * 2);
  ctx.arc(x + 76 * s, y + 8 * s, 22 * s, Math.PI * 1.5, Math.PI * 0.5);
  ctx.closePath();
  ctx.fill();
}

function drawHill(x, y, w, h) {
  ctx.beginPath();
  ctx.moveTo(x, groundY);
  ctx.quadraticCurveTo(x + w * 0.5, y - h, x + w, groundY);
  ctx.closePath();
  ctx.fill();
}

function drawWorld() {
  ctx.fillStyle = "#244333";
  ctx.fillRect(0, groundY, W, H - groundY);

  ctx.fillStyle = "#3f6f52";
  ctx.fillRect(0, groundY, W, 22);

  ctx.strokeStyle = "rgba(255,255,255,0.16)";
  ctx.lineWidth = 3;
  for (let x = -((state.distance * 11) % 52); x < W; x += 52) {
    ctx.beginPath();
    ctx.moveTo(x, groundY + 28);
    ctx.lineTo(x + 28, groundY + 58);
    ctx.stroke();
  }

  for (const obstacle of state.obstacles) {
    if (obstacle.type === "pit") drawPit(obstacle);
    if (obstacle.type === "wall") drawWall(obstacle);
    if (obstacle.type === "crumb") drawCrumbBlock(obstacle);
    if (obstacle.type === "flame") drawFlamePillar(obstacle);
    if (obstacle.type === "flying") drawFlyingObstacle(obstacle);
    if (obstacle.type === "spike" || obstacle.type === "double-spike") drawSpikes(obstacle);
    if (obstacle.type === "hanging") drawHangingObstacle(obstacle);
  }

  for (const platform of state.platforms) {
    drawPlatform(platform);
  }

  for (const jelly of state.jellies) {
    drawJelly(jelly);
  }

  for (const potion of state.potions) {
    drawPotion(potion);
  }

  for (const particle of state.particles) {
    ctx.globalAlpha = Math.max(0, particle.life / 36);
    ctx.fillStyle = particle.color;
    ctx.beginPath();
    ctx.arc(particle.x, particle.y, particle.size, 0, Math.PI * 2);
    ctx.fill();
    ctx.globalAlpha = 1;
  }

  drawHealthBar();
}

function drawPit(obstacle) {
  ctx.fillStyle = "#151820";
  ctx.fillRect(obstacle.x, groundY - 2, obstacle.width, H - groundY + 2);
  ctx.fillStyle = "#2e563f";
  ctx.fillRect(obstacle.x - 10, groundY, 10, 22);
  ctx.fillRect(obstacle.x + obstacle.width, groundY, 10, 22);
  ctx.strokeStyle = "rgba(255,255,255,0.12)";
  ctx.lineWidth = 3;
  ctx.beginPath();
  ctx.moveTo(obstacle.x + 18, groundY + 40);
  ctx.lineTo(obstacle.x + obstacle.width - 18, groundY + 76);
  ctx.stroke();
}

function drawWall(obstacle) {
  if (obstacle.variant === "oven") {
    ctx.fillStyle = obstacle.hit ? "#332a28" : "#5a3c34";
    ctx.fillRect(obstacle.x, obstacle.y, obstacle.width, obstacle.height);
    ctx.fillStyle = "#2b1f1d";
    ctx.fillRect(obstacle.x + 8, obstacle.y + 14, obstacle.width - 16, obstacle.height - 28);
    ctx.fillStyle = obstacle.hit ? "#7b322b" : "#f26b3f";
    ctx.fillRect(obstacle.x + 13, obstacle.y + 26, obstacle.width - 26, obstacle.height - 52);
    ctx.fillStyle = "rgba(255,230,150,0.72)";
    ctx.fillRect(obstacle.x + 18, obstacle.y + 34, obstacle.width - 36, 12);
  } else {
    ctx.fillStyle = obstacle.hit ? "#5b4b44" : obstacle.color;
    ctx.fillRect(obstacle.x, obstacle.y, obstacle.width, obstacle.height);
    ctx.fillStyle = "rgba(255,245,205,0.55)";
    for (let y = obstacle.y + 10; y < groundY; y += 22) {
      ctx.fillRect(obstacle.x + 7, y, obstacle.width - 14, 4);
    }
  }
  ctx.strokeStyle = "rgba(52,33,26,0.45)";
  ctx.lineWidth = 3;
  ctx.strokeRect(obstacle.x, obstacle.y, obstacle.width, obstacle.height);
}

function drawCrumbBlock(obstacle) {
  ctx.fillStyle = obstacle.hit ? "#80583b" : obstacle.color;
  ctx.fillRect(obstacle.x, obstacle.y, obstacle.width, obstacle.height);
  ctx.fillStyle = "#f0c17b";
  ctx.beginPath();
  ctx.arc(obstacle.x + 18, obstacle.y + 18, 5, 0, Math.PI * 2);
  ctx.arc(obstacle.x + 43, obstacle.y + 36, 4, 0, Math.PI * 2);
  ctx.arc(obstacle.x + 23, obstacle.y + 54, 4, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = "rgba(82,45,31,0.55)";
  ctx.lineWidth = 4;
  ctx.strokeRect(obstacle.x, obstacle.y, obstacle.width, obstacle.height);
  ctx.strokeStyle = "rgba(255,242,210,0.35)";
  ctx.lineWidth = 2;
  ctx.beginPath();
  ctx.moveTo(obstacle.x + 12, obstacle.y + 32);
  ctx.lineTo(obstacle.x + 52, obstacle.y + 22);
  ctx.moveTo(obstacle.x + 9, obstacle.y + 51);
  ctx.lineTo(obstacle.x + 45, obstacle.y + 62);
  ctx.stroke();
}

function drawFlamePillar(obstacle) {
  const x = obstacle.x;
  const y = obstacle.y;
  const wave = Math.sin(state.time / 130 + x * 0.03) * 4;
  ctx.fillStyle = "rgba(85, 38, 24, 0.28)";
  ctx.fillRect(x + 5, y + obstacle.height - 8, obstacle.width - 10, 12);
  ctx.fillStyle = obstacle.hit ? "#983d32" : "#f26b3f";
  ctx.beginPath();
  ctx.moveTo(x + 4, groundY);
  ctx.quadraticCurveTo(x + 7, y + 68, x + 20 + wave, y + 36);
  ctx.quadraticCurveTo(x + 25, y + 10, x + 34, y);
  ctx.quadraticCurveTo(x + 48, y + 58, x + obstacle.width - 5, groundY);
  ctx.closePath();
  ctx.fill();
  ctx.fillStyle = "#ffd35b";
  ctx.beginPath();
  ctx.moveTo(x + 16, groundY);
  ctx.quadraticCurveTo(x + 19, y + 78, x + 29 - wave, y + 44);
  ctx.quadraticCurveTo(x + 35, y + 74, x + obstacle.width - 15, groundY);
  ctx.closePath();
  ctx.fill();
}

function drawFlyingObstacle(obstacle) {
  const x = obstacle.x;
  const y = obstacle.y;
  ctx.strokeStyle = "rgba(70, 48, 35, 0.35)";
  ctx.lineWidth = 4;
  ctx.beginPath();
  ctx.moveTo(x + 8, y + obstacle.height + 10);
  ctx.lineTo(x + obstacle.width - 6, y - 8);
  ctx.stroke();

  ctx.fillStyle = obstacle.hit ? "#a8b0b4" : obstacle.color;
  ctx.beginPath();
  ctx.roundRect(x, y, obstacle.width, obstacle.height, 8);
  ctx.fill();
  ctx.fillStyle = "#b43d35";
  for (let i = 0; i < 4; i += 1) {
    ctx.fillRect(x + 14 + i * 22, y + 4, 8, obstacle.height - 8);
  }
  ctx.strokeStyle = "rgba(68,76,82,0.45)";
  ctx.lineWidth = 3;
  ctx.strokeRect(x + 2, y + 2, obstacle.width - 4, obstacle.height - 4);
}

function drawHangingObstacle(obstacle) {
  const x = obstacle.x;
  const y = obstacle.y;
  const bottom = y + obstacle.height;
  const stripe = obstacle.type === "hanging" ? 18 : 16;

  ctx.strokeStyle = "rgba(70, 48, 35, 0.48)";
  ctx.lineWidth = 3;
  for (let chainX = x + 18; chainX < x + obstacle.width; chainX += 38) {
    ctx.beginPath();
    ctx.moveTo(chainX, y - 46);
    ctx.lineTo(chainX + 6, y + 2);
    ctx.stroke();
  }

  ctx.fillStyle = obstacle.hit ? "#7b4640" : obstacle.color;
  ctx.fillRect(x, y, obstacle.width, obstacle.height);

  ctx.fillStyle = "rgba(255, 236, 190, 0.92)";
  for (let stripeX = x + 8; stripeX < x + obstacle.width; stripeX += stripe) {
    ctx.beginPath();
    ctx.moveTo(stripeX, y);
    ctx.lineTo(stripeX + 10, y);
    ctx.lineTo(stripeX - 6, bottom);
    ctx.lineTo(stripeX - 16, bottom);
    ctx.closePath();
    ctx.fill();
  }

  ctx.fillStyle = "rgba(80, 39, 28, 0.35)";
  ctx.fillRect(x, bottom - 8, obstacle.width, 8);

  ctx.strokeStyle = "rgba(255,255,255,0.45)";
  ctx.lineWidth = 3;
  ctx.strokeRect(x + 2, y + 2, obstacle.width - 4, obstacle.height - 4);

  ctx.fillStyle = "#f8d34f";
  for (let flameX = x + 18; flameX < x + obstacle.width; flameX += 32) {
    ctx.beginPath();
    ctx.moveTo(flameX, bottom + 4);
    ctx.quadraticCurveTo(flameX + 9, bottom - 12, flameX + 18, bottom + 4);
    ctx.quadraticCurveTo(flameX + 9, bottom + 14, flameX, bottom + 4);
    ctx.fill();
  }
}

function drawSpikes(obstacle) {
  const spikeCount = obstacle.type === "double-spike" ? 2 : 1;
  for (let i = 0; i < spikeCount; i += 1) {
    const width = obstacle.width / spikeCount;
    const left = obstacle.x + i * width + 5;
    const right = left + width - 10;
    const top = groundY - obstacle.height;
    ctx.fillStyle = obstacle.hit ? "#8e3f43" : obstacle.color;
    ctx.beginPath();
    ctx.moveTo(left, groundY);
    ctx.lineTo((left + right) / 2, top);
    ctx.lineTo(right, groundY);
    ctx.closePath();
    ctx.fill();

    ctx.strokeStyle = "rgba(255,255,255,0.28)";
    ctx.lineWidth = 3;
    ctx.beginPath();
    ctx.moveTo((left + right) / 2, top + 9);
    ctx.lineTo((left + right) / 2, groundY - 12);
    ctx.stroke();
  }
}

function drawPlatform(platform) {
  ctx.fillStyle = "#6a8f6e";
  ctx.fillRect(platform.x, platform.y, platform.width, platform.height);
  ctx.fillStyle = "#d9c59a";
  ctx.fillRect(platform.x, platform.y - 8, platform.width, 12);
  ctx.strokeStyle = "rgba(31,38,48,0.2)";
  ctx.lineWidth = 2;
  for (let x = platform.x + 16; x < platform.x + platform.width; x += 28) {
    ctx.beginPath();
    ctx.moveTo(x, platform.y - 8);
    ctx.lineTo(x, platform.y + 4);
    ctx.stroke();
  }
}

function drawJelly(jelly) {
  const bob = Math.sin(jelly.wobble) * 3;
  const squash = 1 + Math.sin(jelly.wobble * 1.7) * 0.08;
  ctx.fillStyle = jelly.color;
  ctx.beginPath();
  ctx.ellipse(jelly.x, jelly.y + bob, jelly.r * 0.92, jelly.r * 1.15 * squash, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = "rgba(85,45,95,0.35)";
  ctx.lineWidth = 3;
  ctx.stroke();
  ctx.fillStyle = "rgba(255,255,255,0.58)";
  ctx.beginPath();
  ctx.ellipse(jelly.x - 4, jelly.y + bob - 5, 4, 6, -0.45, 0, Math.PI * 2);
  ctx.fill();
}

function drawPotion(potion) {
  const bob = Math.sin(potion.wobble) * 4;
  const x = potion.x;
  const y = potion.y + bob;

  ctx.fillStyle = "rgba(95,199,120,0.22)";
  ctx.beginPath();
  ctx.arc(x, y, potion.r + 9, 0, Math.PI * 2);
  ctx.fill();

  ctx.fillStyle = "#fff8ef";
  ctx.strokeStyle = "rgba(54,83,58,0.45)";
  ctx.lineWidth = 3;
  ctx.beginPath();
  ctx.roundRect(x - 10, y - 18, 20, 32, 6);
  ctx.fill();
  ctx.stroke();

  ctx.fillStyle = "#5fc778";
  ctx.beginPath();
  ctx.roundRect(x - 8, y - 2, 16, 14, 5);
  ctx.fill();

  ctx.fillStyle = "#e14f4f";
  ctx.fillRect(x - 3, y - 15, 6, 10);
  ctx.fillRect(x - 7, y - 11, 14, 4);

  ctx.fillStyle = "rgba(255,255,255,0.72)";
  ctx.beginPath();
  ctx.arc(x - 5, y - 8, 3, 0, Math.PI * 2);
  ctx.fill();
}

function drawHealthBar() {
  const x = 24;
  const y = 24;
  const width = 200;
  const height = 18;
  const ratio = Math.max(0, player.health / getMaxHealth());
  ctx.fillStyle = "rgba(31,38,48,0.32)";
  ctx.fillRect(x, y, width, height);
  ctx.fillStyle = ratio > 0.45 ? "#5fc778" : ratio > 0.22 ? "#f2c84b" : "#e14f4f";
  ctx.fillRect(x, y, width * ratio, height);
  ctx.strokeStyle = "rgba(255,255,255,0.65)";
  ctx.lineWidth = 2;
  ctx.strokeRect(x, y, width, height);
}

function drawPlayer() {
  const blink = player.hurtTimer > 0 && Math.floor(player.hurtTimer / 6) % 2 === 0;
  if (blink) return;

  const phase = player.runPhase;
  const stride = Math.sin(phase);
  const counterStride = Math.sin(phase + Math.PI);
  const legSwing = stride * 0.68;
  const armSwing = counterStride * 0.72;
  const bodyBob = player.grounded ? Math.sin(player.runPhase * 2) * 1.8 : 0;
  const cx = player.x;
  const cy = player.y - 24 + bodyBob;
  const isJumping = !player.grounded && player.vy < 1;
  const isFalling = !player.grounded && player.vy >= 1;
  const tilt = player.grounded ? stride * 0.04 : isJumping ? -0.15 : 0.12;

  if (player.sliding && player.grounded) {
    drawSlidingCookie(cx, player.y, bodyBob);
    ctx.fillStyle = "rgba(0,0,0,0.18)";
    ctx.beginPath();
    ctx.ellipse(player.x, groundY + 8, player.r * 1.28, 7, 0, 0, Math.PI * 2);
    ctx.fill();
    return;
  }

  ctx.save();
  ctx.translate(cx, cy);
  ctx.rotate(tilt);

  if (player.doubleJumpPulse > 0) {
    ctx.globalAlpha = player.doubleJumpPulse / 18;
    ctx.strokeStyle = "#56a8d5";
    ctx.lineWidth = 4;
    ctx.beginPath();
    ctx.arc(0, 0, player.r + 13, 0, Math.PI * 2);
    ctx.stroke();
    ctx.globalAlpha = 1;
  }

  const pose = getRunnerPose(armSwing, legSwing, isJumping, isFalling);
  drawCookieLimb(pose.backArm, 15, "arm");
  drawCookieLimb(pose.backLeg, 17, "leg");
  drawCookieLimb(pose.frontLeg, 17, "leg");
  drawCookieBody();
  drawCookieLimb(pose.frontArm, 15, "arm");
  drawCandyCane(pose.frontArm.to, isJumping, isFalling);
  drawCookieFace(isJumping, isFalling);
  ctx.restore();

  ctx.fillStyle = "rgba(0,0,0,0.18)";
  ctx.beginPath();
  ctx.ellipse(player.x, groundY + 8, player.r * 0.92, 8, 0, 0, Math.PI * 2);
  ctx.fill();
}

function drawSlidingCookie(cx, baseY, bodyBob) {
  ctx.save();
  ctx.translate(cx, baseY + 2 + bodyBob * 0.2);
  ctx.rotate(-0.06);

  ctx.strokeStyle = "#5a2f1d";
  ctx.lineCap = "round";
  ctx.lineJoin = "round";

  ctx.lineWidth = 20;
  ctx.beginPath();
  ctx.moveTo(-5, 14);
  ctx.quadraticCurveTo(-24, 28, -47, 25);
  ctx.stroke();

  ctx.lineWidth = 18;
  ctx.beginPath();
  ctx.moveTo(10, 13);
  ctx.quadraticCurveTo(30, 24, 49, 18);
  ctx.stroke();

  ctx.strokeStyle = "#c98345";
  ctx.lineWidth = 14;
  ctx.beginPath();
  ctx.moveTo(-5, 14);
  ctx.quadraticCurveTo(-24, 28, -47, 25);
  ctx.stroke();

  ctx.beginPath();
  ctx.moveTo(10, 13);
  ctx.quadraticCurveTo(30, 24, 49, 18);
  ctx.stroke();

  const cookie = ctx.createRadialGradient(-10, -18, 4, 0, 2, 54);
  cookie.addColorStop(0, "#f7d39a");
  cookie.addColorStop(0.62, "#c98345");
  cookie.addColorStop(1, "#8a4f2d");
  ctx.fillStyle = cookie;
  ctx.strokeStyle = "#6c3c24";
  ctx.lineWidth = 4;

  ctx.beginPath();
  ctx.ellipse(-6, 6, 35, 18, 0.03, 0, Math.PI * 2);
  ctx.fill();
  ctx.stroke();

  ctx.beginPath();
  ctx.arc(25, -17, 22, 0, Math.PI * 2);
  ctx.fill();
  ctx.stroke();

  ctx.strokeStyle = "#5a2f1d";
  ctx.lineWidth = 17;
  ctx.beginPath();
  ctx.moveTo(-24, 0);
  ctx.quadraticCurveTo(-43, 6, -55, 18);
  ctx.stroke();

  ctx.strokeStyle = "#c98345";
  ctx.lineWidth = 11;
  ctx.beginPath();
  ctx.moveTo(-24, 0);
  ctx.quadraticCurveTo(-43, 6, -55, 18);
  ctx.stroke();

  ctx.fillStyle = "#fff0cf";
  for (const x of [-15, -1, 13]) {
    ctx.beginPath();
    ctx.arc(x, 5, 4, 0, Math.PI * 2);
    ctx.fill();
  }

  ctx.strokeStyle = "#fff0cf";
  ctx.lineWidth = 4.5;
  ctx.lineCap = "round";
  ctx.beginPath();
  ctx.moveTo(3, -24);
  ctx.quadraticCurveTo(16, -22, 25, -34);
  ctx.quadraticCurveTo(36, -22, 47, -28);
  ctx.stroke();

  ctx.fillStyle = "#1f9ed6";
  ctx.beginPath();
  ctx.ellipse(17, -16, 7, 8, -0.28, 0, Math.PI * 2);
  ctx.ellipse(34, -16, 7, 8, 0.28, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = "#fff0cf";
  ctx.lineWidth = 2;
  ctx.stroke();

  ctx.fillStyle = "#0f3a58";
  ctx.beginPath();
  ctx.arc(19, -15, 2.7, 0, Math.PI * 2);
  ctx.arc(33, -15, 2.7, 0, Math.PI * 2);
  ctx.fill();

  ctx.strokeStyle = "#2b1e18";
  ctx.lineWidth = 3;
  ctx.beginPath();
  ctx.arc(26, -3, 6, 0.1, Math.PI - 0.1);
  ctx.stroke();

  ctx.save();
  ctx.translate(48, -1);
  ctx.rotate(1.28);
  drawCandyCane([0, 0], false, true);
  ctx.restore();
  ctx.restore();
}

function getRunnerPose(armSwing, legSwing, isJumping, isFalling) {
  if (player.hurtTimer > 0) {
    return {
      frontArm: { from: [18, -3], elbow: [29, 5], to: [35, 17] },
      backArm: { from: [-18, -3], elbow: [-30, -6], to: [-36, -18] },
      frontLeg: { from: [10, 32], knee: [13, 47], to: [17, 55] },
      backLeg: { from: [-10, 32], knee: [-13, 47], to: [-17, 55] },
    };
  }

  if (isJumping) {
    return {
      frontArm: { from: [18, -4], elbow: [27, -24], to: [17, -39] },
      backArm: { from: [-18, -4], elbow: [-27, -24], to: [-17, -39] },
      frontLeg: { from: [10, 32], knee: [16, 39], to: [20, 32] },
      backLeg: { from: [-10, 32], knee: [-13, 47], to: [-18, 46] },
    };
  }

  if (isFalling) {
    return {
      frontArm: { from: [18, -4], elbow: [31, -1], to: [38, -13] },
      backArm: { from: [-18, -4], elbow: [-30, 5], to: [-36, 17] },
      frontLeg: { from: [10, 32], knee: [14, 49], to: [18, 57] },
      backLeg: { from: [-10, 32], knee: [-14, 47], to: [-18, 52] },
    };
  }

  return {
    frontArm: {
      from: [18, -3],
      elbow: [28, 3 + armSwing * 8],
      to: [36, 14 + armSwing * 12],
    },
    backArm: {
      from: [-18, -3],
      elbow: [-28, 3 - armSwing * 8],
      to: [-36, 14 - armSwing * 12],
    },
    frontLeg: {
      from: [10, 32],
      knee: [12 + legSwing * 6, 48 - Math.abs(legSwing) * 6],
      to: [16 + legSwing * 9, 56 - Math.max(0, legSwing) * 10],
    },
    backLeg: {
      from: [-10, 32],
      knee: [-12 - legSwing * 6, 48 - Math.abs(legSwing) * 6],
      to: [-16 - legSwing * 9, 56 + Math.min(0, legSwing) * 10],
    },
  };
}

function drawCookieLimb(limb, width, kind) {
  const joint = limb.elbow || limb.knee;
  ctx.strokeStyle = "#5a2f1d";
  ctx.lineWidth = width + 6;
  ctx.lineCap = "round";
  ctx.lineJoin = "round";
  ctx.beginPath();
  ctx.moveTo(limb.from[0], limb.from[1]);
  ctx.quadraticCurveTo(joint[0], joint[1], limb.to[0], limb.to[1]);
  ctx.stroke();

  ctx.strokeStyle = "#c98345";
  ctx.lineWidth = width;
  ctx.beginPath();
  ctx.moveTo(limb.from[0], limb.from[1]);
  ctx.quadraticCurveTo(joint[0], joint[1], limb.to[0], limb.to[1]);
  ctx.stroke();

  ctx.fillStyle = "#c98345";
  ctx.strokeStyle = "#5a2f1d";
  ctx.lineWidth = 3;
  ctx.beginPath();
  if (kind === "leg") {
    ctx.ellipse(limb.to[0], limb.to[1] + 1, width * 0.68, width * 0.44, 0.1, 0, Math.PI * 2);
  } else {
    ctx.ellipse(limb.to[0], limb.to[1], width * 0.55, width * 0.5, -0.15, 0, Math.PI * 2);
  }
  ctx.fill();
  ctx.stroke();

  ctx.fillStyle = "rgba(255,240,207,0.85)";
  if (kind === "leg") {
    ctx.fillRect(limb.to[0] - width * 0.32, limb.to[1] - 2, width * 0.64, 3);
  } else {
    ctx.beginPath();
    ctx.arc(limb.to[0] - 1, limb.to[1] - 1, width * 0.17, 0, Math.PI * 2);
    ctx.fill();
  }
}

function drawCookieBody() {
  const cookie = ctx.createRadialGradient(-9, -38, 4, 0, -16, 58);
  cookie.addColorStop(0, "#f7d39a");
  cookie.addColorStop(0.62, "#c98345");
  cookie.addColorStop(1, "#8a4f2d");

  // Clean torso only. Legs are drawn behind it so the joints are hidden.
  ctx.fillStyle = cookie;
  ctx.beginPath();
  ctx.moveTo(-17, -9);
  ctx.bezierCurveTo(-27, -1, -27, 16, -19, 29);
  ctx.bezierCurveTo(-13, 38, 13, 38, 19, 29);
  ctx.bezierCurveTo(27, 16, 27, -1, 17, -9);
  ctx.closePath();
  ctx.fill();
  ctx.strokeStyle = "#6c3c24";
  ctx.lineWidth = 4;
  ctx.stroke();

  ctx.beginPath();
  ctx.arc(0, -34, 27, 0, Math.PI * 2);
  ctx.fill();
  ctx.stroke();

  ctx.fillStyle = "#fff0cf";
  for (const y of [0, 12, 24]) {
    ctx.beginPath();
    ctx.arc(0, y, 4.2, 0, Math.PI * 2);
    ctx.fill();
    ctx.strokeStyle = "#f7d39a";
    ctx.lineWidth = 1.5;
    ctx.stroke();
  }

  ctx.strokeStyle = "#fff0cf";
  ctx.lineWidth = 4.5;
  ctx.lineCap = "round";
  ctx.beginPath();
  ctx.moveTo(-27, -44);
  ctx.quadraticCurveTo(-10, -39, 2, -55);
  ctx.quadraticCurveTo(12, -40, 27, -48);
  ctx.stroke();

  ctx.beginPath();
  ctx.moveTo(-17, -25);
  ctx.quadraticCurveTo(-7, -32, 2, -24);
  ctx.quadraticCurveTo(12, -33, 20, -24);
  ctx.stroke();
}

function drawCookieFace(isJumping, isFalling) {
  const eyeY = isJumping ? -36 : -33;

  ctx.fillStyle = "#1f9ed6";
  ctx.beginPath();
  ctx.ellipse(-10, eyeY, 8, 9, -0.35, 0, Math.PI * 2);
  ctx.ellipse(11, eyeY, 8, 9, 0.35, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = "#fff0cf";
  ctx.lineWidth = 2;
  ctx.stroke();

  ctx.fillStyle = "#0f3a58";
  ctx.beginPath();
  ctx.arc(-8, eyeY + 1, 3.1, 0, Math.PI * 2);
  ctx.arc(9, eyeY + 1, 3.1, 0, Math.PI * 2);
  ctx.fill();

  ctx.fillStyle = "#fff";
  ctx.beginPath();
  ctx.arc(-12, eyeY - 3, 2.1, 0, Math.PI * 2);
  ctx.arc(7, eyeY - 3, 2.1, 0, Math.PI * 2);
  ctx.fill();

  ctx.strokeStyle = "#fff0cf";
  ctx.lineWidth = 4;
  ctx.lineCap = "round";
  ctx.beginPath();
  ctx.moveTo(-21, -49);
  ctx.lineTo(-6, -45);
  ctx.moveTo(6, -45);
  ctx.lineTo(21, -50);
  ctx.stroke();

  ctx.strokeStyle = "#2b1e18";
  ctx.lineWidth = 3;
  ctx.beginPath();
  if (player.hurtTimer > 0) {
    ctx.moveTo(-8, -19);
    ctx.lineTo(8, -19);
  } else if (isFalling) {
    ctx.arc(1, -20, 5, Math.PI, Math.PI * 2);
  } else {
    ctx.arc(1, -22, 7, 0.15, Math.PI - 0.15);
  }
  ctx.stroke();

  ctx.fillStyle = "rgba(239, 82, 82, 0.78)";
  ctx.beginPath();
  ctx.arc(-18, -23, 4.2, 0, Math.PI * 2);
  ctx.arc(19, -23, 4.2, 0, Math.PI * 2);
  ctx.fill();
}

function drawCandyCane(hand, isJumping, isFalling) {
  const angle = isJumping ? -0.8 : isFalling ? -0.25 : -0.45;
  ctx.save();
  ctx.translate(hand[0] + 3, hand[1] - 2);
  ctx.rotate(angle);

  ctx.strokeStyle = "#fff8ef";
  ctx.lineWidth = 6;
  ctx.lineCap = "round";
  ctx.beginPath();
  ctx.moveTo(0, 18);
  ctx.lineTo(0, -18);
  ctx.quadraticCurveTo(0, -34, 14, -34);
  ctx.stroke();

  ctx.strokeStyle = "#e33a3a";
  ctx.lineWidth = 4;
  for (let y = 14; y > -18; y -= 14) {
    ctx.beginPath();
    ctx.moveTo(-4, y);
    ctx.lineTo(4, y - 6);
    ctx.stroke();
  }
  ctx.beginPath();
  ctx.moveTo(1, -26);
  ctx.lineTo(11, -32);
  ctx.stroke();

  ctx.restore();
}

function loop(now) {
  const dt = Math.min(now - state.lastFrame, 34);
  state.lastFrame = now;
  update(dt);
  draw();
}

if (playButton) {
  playButton.addEventListener("click", startRun);
}

if (menuButton) {
  menuButton.addEventListener("click", showMenu);
}

startButton.addEventListener("click", () => {
  if (state.mode === "paused") {
    pauseGame();
    requestAnimationFrame(loop);
  } else if (state.mode === "menu") {
    startRun();
  } else {
    startRun();
  }
});

window.addEventListener("keydown", (event) => {
  if (slideKeys.includes(event.code)) {
    event.preventDefault();
  }
  if (["Space", "ArrowUp"].includes(event.code)) {
    event.preventDefault();
    if (state.mode === "menu" || state.mode === "gameover") {
      startRun();
    } else {
      jump();
    }
  }
  if (event.code === "KeyP" && state.mode !== "menu") pauseGame();
  if (event.code === "KeyR") {
    startRun();
  }
  state.keys.add(event.code);
});

window.addEventListener("keyup", (event) => {
  if (slideKeys.includes(event.code)) {
    event.preventDefault();
  }
  if (["Space", "ArrowUp"].includes(event.code)) {
    player.jumpHold = 0;
  }
  state.keys.delete(event.code);
});

renderMenu();
draw();
