const canvas = document.querySelector("#gameCanvas");
const ctx = canvas.getContext("2d");

const distanceText = document.querySelector("#distanceText");
const scoreText = document.querySelector("#scoreText");
const bestText = document.querySelector("#bestText");
const overlay = document.querySelector("#overlay");
const overlayTitle = document.querySelector("#overlayTitle");
const overlayText = document.querySelector("#overlayText");
const startButton = document.querySelector("#startButton");

const W = canvas.width;
const H = canvas.height;
const groundY = 440;
const gravity = 0.82;
const jumpVelocity = -16.2;
const maxFallSpeed = 18;

const state = {
  mode: "ready",
  time: 0,
  speed: 5.4,
  distance: 0,
  score: 0,
  best: Number(localStorage.getItem("rollingDashBestV1") || 0),
  spawnTimer: 0,
  gapTimer: 0,
  obstacles: [],
  particles: [],
  keys: new Set(),
  lastFrame: 0,
};

const player = {
  x: 150,
  y: groundY - 28,
  r: 28,
  vy: 0,
  grounded: true,
  jumpHold: 0,
  rotation: 0,
};

bestText.textContent = String(state.best);

const obstacleTypes = [
  { type: "spike", width: 44, height: 48, color: "#e14f4f" },
  { type: "wall", width: 40, height: 92, color: "#62564c" },
  { type: "pit", width: 130, height: 0, color: "#151820" },
  { type: "double-spike", width: 92, height: 52, color: "#e14f4f" },
];

function resetGame() {
  state.mode = "running";
  state.time = 0;
  state.speed = 5.4;
  state.distance = 0;
  state.score = 0;
  state.spawnTimer = 42;
  state.gapTimer = 0;
  state.obstacles = [];
  state.particles = [];
  state.lastFrame = performance.now();

  player.x = 150;
  player.y = groundY - player.r;
  player.vy = 0;
  player.grounded = true;
  player.jumpHold = 0;
  player.rotation = 0;

  overlay.classList.add("hidden");
  updateStats();
}

function endGame(reason) {
  state.mode = "gameover";
  state.best = Math.max(state.best, state.score);
  localStorage.setItem("rollingDashBestV1", String(state.best));
  bestText.textContent = String(state.best);

  overlayTitle.textContent = "기록 종료";
  overlayText.textContent = `${reason} 최종 거리 ${Math.floor(state.distance)}m, 점수 ${state.score}점입니다.`;
  startButton.textContent = "다시 시작";
  overlay.querySelector(".status-label").textContent = "GAME OVER";
  overlay.classList.remove("hidden");
}

function pauseGame() {
  if (state.mode === "running") {
    state.mode = "paused";
    overlayTitle.textContent = "일시정지";
    overlayText.textContent = "P 키를 다시 누르거나 버튼을 눌러 계속합니다.";
    startButton.textContent = "계속";
    overlay.querySelector(".status-label").textContent = "PAUSED";
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
}

function jump() {
  if (!player.grounded || state.mode !== "running") return;
  player.vy = jumpVelocity;
  player.grounded = false;
  player.jumpHold = 9;
  spawnDust(player.x - 12, player.y + player.r, 10, "#f8f4e8");
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

function createObstacle() {
  const roll = Math.random();
  let blueprint;

  if (state.distance < 140) {
    blueprint = obstacleTypes[0];
  } else if (roll < 0.38) {
    blueprint = obstacleTypes[0];
  } else if (roll < 0.62) {
    blueprint = obstacleTypes[1];
  } else if (roll < 0.8) {
    blueprint = obstacleTypes[2];
  } else {
    blueprint = obstacleTypes[3];
  }

  const obstacle = {
    ...blueprint,
    x: W + 30,
    y: blueprint.type === "pit" ? groundY : groundY - blueprint.height,
    passed: false,
  };

  state.obstacles.push(obstacle);
}

function update(dt) {
  if (state.mode !== "running") return;

  const scale = Math.min(dt / 16.67, 2);
  state.time += dt;
  state.distance += state.speed * scale * 0.17;
  state.speed = Math.min(10.8, 5.4 + state.distance / 620);

  if ((state.keys.has("Space") || state.keys.has("ArrowUp")) && player.jumpHold > 0) {
    player.vy -= 0.34 * scale;
    player.jumpHold -= scale;
  }

  player.vy = Math.min(maxFallSpeed, player.vy + gravity * scale);
  player.y += player.vy * scale;
  player.rotation += state.speed * 0.024 * scale;

  const onPit = isPlayerOverPit();
  if (!onPit && player.y + player.r >= groundY) {
    if (!player.grounded && player.vy > 2) {
      spawnDust(player.x - 8, groundY, 8, "#d4e6d6");
    }
    player.y = groundY - player.r;
    player.vy = 0;
    player.grounded = true;
    player.jumpHold = 0;
  } else {
    player.grounded = false;
  }

  if (player.y - player.r > H) {
    endGame("절벽 아래로 떨어졌습니다.");
    return;
  }

  state.spawnTimer -= scale;
  if (state.spawnTimer <= 0) {
    createObstacle();
    const difficultyGap = Math.max(70, 132 - state.distance / 28);
    state.spawnTimer = difficultyGap + Math.random() * 55;
  }

  for (const obstacle of state.obstacles) {
    obstacle.x -= state.speed * scale;
    if (!obstacle.passed && obstacle.x + obstacle.width < player.x - player.r) {
      obstacle.passed = true;
      state.score += obstacle.type === "pit" ? 2 : 1;
      updateStats();
    }
  }

  state.obstacles = state.obstacles.filter((obstacle) => obstacle.x + obstacle.width > -80);

  for (const particle of state.particles) {
    particle.x += particle.vx * scale;
    particle.y += particle.vy * scale;
    particle.vy += 0.14 * scale;
    particle.life -= scale;
  }
  state.particles = state.particles.filter((particle) => particle.life > 0);

  const hit = state.obstacles.some(collidesWithPlayer);
  if (hit) {
    spawnDust(player.x, player.y, 28, "#e14f4f");
    endGame("장애물에 부딪혔습니다.");
  }

  updateStats();
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
      if (circleHitsTriangle(player, triangle)) return true;
    }
    return false;
  }

  return circleHitsRect(
    player.x,
    player.y,
    player.r,
    obstacle.x,
    obstacle.y,
    obstacle.width,
    obstacle.height,
  );
}

function circleHitsRect(cx, cy, radius, rx, ry, rw, rh) {
  const closestX = Math.max(rx, Math.min(cx, rx + rw));
  const closestY = Math.max(ry, Math.min(cy, ry + rh));
  const dx = cx - closestX;
  const dy = cy - closestY;
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
    if (obstacle.type === "spike" || obstacle.type === "double-spike") drawSpikes(obstacle);
  }

  for (const particle of state.particles) {
    ctx.globalAlpha = Math.max(0, particle.life / 36);
    ctx.fillStyle = particle.color;
    ctx.beginPath();
    ctx.arc(particle.x, particle.y, particle.size, 0, Math.PI * 2);
    ctx.fill();
    ctx.globalAlpha = 1;
  }
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
  ctx.fillStyle = obstacle.color;
  ctx.fillRect(obstacle.x, obstacle.y, obstacle.width, obstacle.height);
  ctx.fillStyle = "rgba(255,255,255,0.16)";
  for (let y = obstacle.y + 10; y < groundY; y += 22) {
    ctx.fillRect(obstacle.x + 7, y, obstacle.width - 14, 4);
  }
}

function drawSpikes(obstacle) {
  const spikeCount = obstacle.type === "double-spike" ? 2 : 1;
  for (let i = 0; i < spikeCount; i += 1) {
    const width = obstacle.width / spikeCount;
    const left = obstacle.x + i * width + 5;
    const right = left + width - 10;
    const top = groundY - obstacle.height;
    ctx.fillStyle = obstacle.color;
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

function drawPlayer() {
  ctx.save();
  ctx.translate(player.x, player.y);
  ctx.rotate(player.rotation);

  const body = ctx.createRadialGradient(-10, -12, 4, 0, 0, player.r);
  body.addColorStop(0, "#fff2a8");
  body.addColorStop(0.45, "#f2c84b");
  body.addColorStop(1, "#d28b2d");

  ctx.fillStyle = body;
  ctx.beginPath();
  ctx.arc(0, 0, player.r, 0, Math.PI * 2);
  ctx.fill();

  ctx.strokeStyle = "rgba(31,38,48,0.22)";
  ctx.lineWidth = 4;
  ctx.stroke();

  ctx.strokeStyle = "rgba(31,38,48,0.38)";
  ctx.lineWidth = 3;
  ctx.beginPath();
  ctx.moveTo(-14, -16);
  ctx.lineTo(14, 16);
  ctx.moveTo(14, -16);
  ctx.lineTo(-14, 16);
  ctx.stroke();
  ctx.restore();

  ctx.fillStyle = "rgba(0,0,0,0.18)";
  ctx.beginPath();
  ctx.ellipse(player.x, groundY + 8, player.r * 0.85, 8, 0, 0, Math.PI * 2);
  ctx.fill();
}

function loop(now) {
  const dt = Math.min(now - state.lastFrame, 34);
  state.lastFrame = now;
  update(dt);
  draw();
}

startButton.addEventListener("click", () => {
  if (state.mode === "paused") {
    pauseGame();
    requestAnimationFrame(loop);
  } else {
    resetGame();
    requestAnimationFrame(loop);
  }
});

window.addEventListener("keydown", (event) => {
  if (["Space", "ArrowUp"].includes(event.code)) {
    event.preventDefault();
    if (state.mode === "ready" || state.mode === "gameover") {
      resetGame();
      requestAnimationFrame(loop);
    } else {
      jump();
    }
  }
  if (event.code === "KeyP") pauseGame();
  if (event.code === "KeyR") {
    resetGame();
    requestAnimationFrame(loop);
  }
  state.keys.add(event.code);
});

window.addEventListener("keyup", (event) => {
  if (["Space", "ArrowUp"].includes(event.code)) {
    player.jumpHold = 0;
  }
  state.keys.delete(event.code);
});

draw();
