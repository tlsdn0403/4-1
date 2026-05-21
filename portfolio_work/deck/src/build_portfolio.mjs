import fs from "node:fs";
import path from "node:path";
import {
  Presentation,
  PresentationFile,
  row,
  column,
  grid,
  layers,
  panel,
  text,
  image,
  shape,
  rule,
  fill,
  hug,
  fixed,
  wrap,
  fr,
} from "@oai/artifact-tool";

const W = 1920;
const H = 1080;
const FONT = "Malgun Gothic";

const ROOT = path.resolve(".");
const REPORT = path.resolve(ROOT, "..", "report_images");
const GAME_ASSETS = path.resolve(ROOT, "scratch", "assets");

const C = {
  ink: "#101214",
  night: "#151A18",
  deep: "#1C251F",
  card: "#243026",
  paper: "#F5F2E8",
  soft: "#DAD6C8",
  muted: "#A9B4A8",
  amber: "#F0BE45",
  moss: "#91A765",
  rust: "#C76540",
  blue: "#77A6C8",
  gray: "#2D3134",
  black: "#070808",
};

const A = {
  hero: path.join(GAME_ASSETS, "hero_truck_escape.jpg"),
  truckView: path.join(GAME_ASSETS, "stage2_truck_view.jpg"),
  routeView: path.join(GAME_ASSETS, "stage2_route_view.jpg"),
  sideTruck: path.join(GAME_ASSETS, "truck_side_view.jpg"),
  itemFlow: path.join(REPORT, "w04_p01_01_855x830.jpg"),
  truckFlow: path.join(REPORT, "w04_p01_02_798x917.jpg"),
  inventoryLog: path.join(REPORT, "w04_p01_03_667x336.jpg"),
  triggerEnum: path.join(REPORT, "w12_p01_02_490x214.jpg"),
  cargoRide: path.join(REPORT, "w12_p03_01_611x662.jpg"),
  cargoBoxesCode: path.join(REPORT, "w13_p01_01_1047x724.jpg"),
  cargoBoxesView: path.join(REPORT, "w13_p01_02_721x489.jpg"),
  mountedCtor: path.join(REPORT, "w13_p03_02_1333x334.jpg"),
  mountedAimCode: path.join(REPORT, "w13_p03_04_1438x602.jpg"),
  mountedView: path.join(REPORT, "w13_p05_01_1494x1058.jpg"),
  shellCode: path.join(REPORT, "w14_p08_01_544x282.jpg"),
  shellView: path.join(REPORT, "w14_p08_02_609x477.jpg"),
  stageSketch: path.join(REPORT, "w18_p02_01_1603x766.jpg"),
  tileMarkerCode: path.join(REPORT, "w18_p02_02_990x388.jpg"),
  stageOverview: path.join(REPORT, "w18_p08_01_1864x1082.jpg"),
  stageFog: path.join(REPORT, "w18_p09_01_2017x1106.jpg"),
  startGeneration: path.join(REPORT, "w18_p04_01_649x653.jpg"),
  activeTilesCode: path.join(REPORT, "w18_p06_01_1221x499.jpg"),
  truckStagePlay: path.join(REPORT, "w18_p10_01_1262x754.jpg"),
  transitionCode: path.join(REPORT, "w20_p01_01_744x342.jpg"),
};

const presentation = Presentation.create({
  slideSize: { width: W, height: H },
});

function assetDataUrl(src) {
  const abs = path.isAbsolute(src) ? src : path.resolve(src);
  const ext = path.extname(abs).toLowerCase();
  const contentType = ext === ".png" ? "image/png" : "image/jpeg";
  return {
    dataUrl: `data:${contentType};base64,${fs.readFileSync(abs).toString("base64")}`,
    contentType,
  };
}

function T(value, options = {}) {
  return text(value, {
    name: options.name,
    width: options.width ?? fill,
    height: options.height ?? hug,
    columnSpan: options.columnSpan,
    rowSpan: options.rowSpan,
    style: {
      fontFamily: FONT,
      color: options.color ?? C.paper,
      fontSize: options.size ?? 28,
      bold: options.bold ?? false,
      italic: options.italic ?? false,
      alignment: options.align ?? "left",
      lineSpacing: options.lineSpacing ?? 1.08,
    },
  });
}

function Eyebrow(value, color = C.amber) {
  return T(value, { size: 17, bold: true, color, width: wrap(760) });
}

function Title(value, width = fill) {
  return T(value, { name: "slide-title", size: 56, bold: true, width, lineSpacing: 0.96 });
}

function BigTitle(value, width = fill) {
  return T(value, { size: 76, bold: true, width, lineSpacing: 0.9 });
}

function Body(value, width = fill) {
  return T(value, { size: 25, color: C.soft, width, lineSpacing: 1.12 });
}

function Small(value, width = fill, color = C.muted) {
  return T(value, { size: 18, color, width, lineSpacing: 1.12 });
}

function Caption(value, color = C.muted) {
  return T(value, { size: 15, color, width: fill, lineSpacing: 1.05 });
}

function ImageBox(src, alt, opts = {}) {
  const source = assetDataUrl(src);
  return panel(
    {
      width: opts.width ?? fill,
      height: opts.height ?? fill,
      fill: opts.bg ?? C.black,
      borderRadius: opts.radius ?? 8,
      padding: opts.padding ?? 0,
      columnSpan: opts.columnSpan,
      rowSpan: opts.rowSpan,
    },
    image({
      ...source,
      fit: opts.fit ?? "cover",
      width: fill,
      height: fill,
      borderRadius: opts.radius ?? 8,
      alt,
    }),
  );
}

function Card(title, body, accent = C.amber, opts = {}) {
  return panel(
    {
      width: opts.width ?? fill,
      height: opts.height ?? hug,
      padding: opts.padding ?? { x: 26, y: 22 },
      fill: opts.fill ?? C.card,
      borderRadius: 8,
    },
    column(
      { width: fill, height: hug, gap: 10 },
      [
        T(title, { size: opts.titleSize ?? 24, bold: true, color: accent }),
        typeof body === "string" ? Small(body, fill, opts.bodyColor ?? C.soft) : body,
      ],
    ),
  );
}

function Step(label, title, detail, accent = C.amber) {
  return panel(
    { width: fill, height: hug, padding: { x: 20, y: 18 }, fill: "#202720", borderRadius: 8 },
    column(
      { width: fill, height: hug, gap: 7 },
      [
        T(label, { size: 16, bold: true, color: accent }),
        T(title, { size: 25, bold: true, color: C.paper }),
        Small(detail, fill, C.soft),
      ],
    ),
  );
}

function Arrow() {
  return T("→", { size: 34, bold: true, color: C.amber, width: fixed(34), align: "center" });
}

function Bullet(title, detail, accent = C.amber) {
  return row(
    { width: fill, height: hug, gap: 14, align: "start" },
    [
      shape({ width: fixed(10), height: fixed(10), fill: accent, borderRadius: 5 }),
      column(
        { width: fill, height: hug, gap: 4 },
        [
          T(title, { size: 22, bold: true, color: C.paper }),
          Small(detail, fill, C.soft),
        ],
      ),
    ],
  );
}

function Evidence(label) {
  return panel(
    { width: hug, height: hug, padding: { x: 14, y: 6 }, fill: "#31362D", borderRadius: 7 },
    T(label, { size: 14, bold: true, color: C.amber, width: hug }),
  );
}

function Slide(children, bg = C.ink, padding = { x: 84, y: 64 }, gap = 32) {
  const slide = presentation.slides.add();
  slide.compose(
    layers(
      { width: fill, height: fill },
      [
        shape({ width: fill, height: fill, fill: bg }),
        column({ width: fill, height: fill, padding, gap }, children),
      ],
    ),
    {
      frame: { left: 0, top: 0, width: W, height: H },
      baseUnit: 8,
    },
  );
  return slide;
}

// 01 Cover
Slide(
  [
    grid(
      { width: fill, height: fill, columns: [fr(0.82), fr(1.18)], columnGap: 48 },
      [
        column(
          { width: fill, height: fill, gap: 28, justify: "between" },
          [
            column(
              { width: fill, height: hug, gap: 26 },
              [
                Eyebrow("COM2US INTERNSHIP PORTFOLIO", C.amber),
                BigTitle("감염:\n죽음의 도시"),
                rule({ width: fixed(220), stroke: C.amber, weight: 5 }),
                Body("트럭을 중심으로 파밍, 적재, 탑승, 무기, 스테이지 전환을 연결한 Unreal Engine 5 C++ 졸업작품 포트폴리오입니다.", wrap(650)),
              ],
            ),
            column(
              { width: fill, height: hug, gap: 8 },
              [
                T("박신우", { size: 34, bold: true }),
                Small("Game Client / Gameplay System Programmer"),
              ],
            ),
          ],
        ),
        ImageBox(A.hero, "Truck gameplay screenshot", { radius: 0 }),
      ],
    ),
  ],
  C.night,
  { x: 84, y: 76 },
);

// 02 Positioning
Slide([
  column(
    { width: fill, height: hug, gap: 14 },
    [
      Eyebrow("ROLE SUMMARY"),
      Title("저는 트럭을 하나의 이동 수단이 아니라,\n게임 루프를 묶는 중심 객체로 설계했습니다"),
      Body("플레이어의 행동이 파밍, 적재, 탑승, 무기 사용, 스테이지 전환으로 자연스럽게 이어지도록 트럭을 상태 흐름의 중심에 두고 구조를 재설계했습니다.", wrap(1380)),
    ],
  ),
  row(
    { width: fill, height: hug, gap: 15, align: "center" },
    [
      Step("01", "파밍", "공통 상호작용과 아이템 부모 클래스"),
      Arrow(),
      Step("02", "트럭 적재", "인벤토리 타입을 트럭 상태로 전달"),
      Arrow(),
      Step("03", "탑승/이동", "운전석, 적재칸, 거치총 상호작용 분리"),
      Arrow(),
      Step("04", "2스테이지", "타일 기반으로 길을 이어 붙이는 구조"),
    ],
  ),
  grid(
    { width: fill, height: hug, columns: [fr(1), fr(1), fr(1)], columnGap: 26 },
    [
      Card("보여줄 역량", "시스템을 따로 구현하는 것이 아니라, 상태와 책임을 나누어 플레이 루프가 끊기지 않게 연결했습니다.", C.amber),
      Card("설계 근거", "상호작용 흐름도, 충돌 원인 분석, 타일 연결 스케치처럼 구현 전에 구조를 먼저 검토한 흔적을 시각 자료로 사용했습니다.", C.moss),
      Card("의도적으로 줄인 내용", "좀비 AI 세부 구현은 핵심 어필에서 제외하고, 내가 구조를 잡은 트럭/스테이지/상호작용에 집중했습니다.", C.rust),
    ],
  ),
]);

// 03 Evidence timeline
Slide([
  column(
    { width: fill, height: hug, gap: 14 },
    [
      Eyebrow("DEVELOPMENT EVIDENCE", C.moss),
      Title("기능 나열보다 구조 변화와 문제 해결 흐름을 먼저 보여줍니다"),
      Body("결과 화면만 나열하지 않고, 상호작용 상태가 어떻게 확장되고 어떤 병목이 다음 설계 변경으로 이어졌는지를 중심으로 구성했습니다.", wrap(1280)),
    ],
  ),
  grid(
    { width: fill, height: hug, columns: [fr(1), fr(1), fr(1), fr(1)], columnGap: 24 },
    [
      Step("기반", "상호작용 시스템", "IInteractInterface, UInteractTriggerComponent, ALootItemBase로 파밍 구조 정리", C.amber),
      Step("확장", "트럭 구조화", "운전석/적재칸/거치총 트리거 분리, 캐릭터 부착, 충돌 박스 분리", C.moss),
      Step("조작감", "거치형 기관총", "Yaw/Pitch 축, 카메라 기준 조준, 총구 보정, 탄피/반동 피드백", C.blue),
      Step("스테이지", "Stage2 타일 구조", "Entry/Exit/Trigger 기반의 TileMarker와 TileManager 연결", C.rust),
    ],
  ),
  Small("핵심 구현 파일: ATruck, AMountedMachineGun, AStage2TileManager, UInteractTriggerComponent", fill),
]);

// 04 Interaction architecture
Slide([
  grid(
    { width: fill, height: fill, columns: [fr(1.02), fr(0.98)], columnGap: 42 },
    [
      column(
        { width: fill, height: fill, gap: 22 },
        [
          Eyebrow("SYSTEM 01"),
          Title("파밍은 단순 획득이 아니라,\n이후 트럭 적재로 이어질 상태를 만드는 구조입니다"),
          Body("처음에는 인벤토리를 무게값으로만 볼 수 있었지만, 트럭이 어떤 아이템을 실었는지 알아야 했기 때문에 `EItemType` 배열 구조로 바꾸었습니다.", wrap(760)),
          Card(
            "설계 판단",
            column(
              { width: fill, height: hug, gap: 10 },
              [
                Bullet("공통 인터페이스", "아이템, 트럭, 문처럼 상호작용 가능한 액터를 같은 방식으로 호출"),
                Bullet("범위 기반 등록", "트리거에 들어오면 상호작용 대상을 캐릭터에 등록하고, 벗어나면 해제"),
                Bullet("타입 보존", "아이템을 트럭으로 넘길 때 무게만이 아니라 아이템 종류를 유지"),
              ],
            ),
            C.amber,
          ),
        ],
      ),
      column(
        { width: fill, height: fill, gap: 20 },
        [
          column({ width: fill, height: fill, gap: 8 }, [Evidence("아이템 상호작용 흐름 설계"), ImageBox(A.itemFlow, "Item interaction flow sketch", { fit: "contain", bg: "#F6F3EA" })]),
          column({ width: fill, height: fill, gap: 8 }, [Evidence("트럭 적재 상호작용 흐름 설계"), ImageBox(A.truckFlow, "Truck interaction flow sketch", { fit: "contain", bg: "#F6F3EA" })]),
        ],
      ),
    ],
  ),
]);

// 05 Truck interaction hub
Slide([
  grid(
    { width: fill, height: fill, columns: [fr(0.92), fr(1.08)], columnGap: 44 },
    [
      column(
        { width: fill, height: fill, gap: 22 },
        [
          Eyebrow("SYSTEM 02", C.moss),
          Title("트럭은 세 가지 역할을 가진 허브로 분리했습니다"),
          Body("같은 F키 상호작용이어도 접근한 위치에 따라 운전, 적재칸 탑승, 거치총 사용이 달라져야 했습니다. 그래서 트럭 내부 상태를 위치/역할 단위로 나눴습니다.", wrap(760)),
          grid(
            { width: fill, height: hug, columns: [fr(1), fr(1), fr(1)], columnGap: 14 },
            [
              Card("DriverSeat", "트럭 조작 권한과 운전석 부착", C.amber, { padding: { x: 18, y: 16 } }),
              Card("CargoSeat", "적재칸 탑승과 이동 가능 영역", C.moss, { padding: { x: 18, y: 16 } }),
              Card("TurretSeat", "거치형 기관총 사용 상태", C.blue, { padding: { x: 18, y: 16 } }),
            ],
          ),
          Card("객체 지향 설계", "ATruck 생성자에서 Driver/Cargo/Turret 트리거를 분리하고 `ETruckInteractType`으로 분기합니다. DriverCharacter, MountedWeaponUser 같은 런타임 포인터는 private로 감추고 Getter/Setter로 접근 통로를 제한했습니다.", C.rust),
        ],
      ),
      column(
        { width: fill, height: fill, gap: 18 },
        [
          ImageBox(A.sideTruck, "Truck side view", { height: fixed(520), fit: "cover" }),
          row(
            { width: fill, height: fill, gap: 18 },
            [
              column({ width: fill, height: fill, gap: 8 }, [Evidence("상호작용 타입 enum"), ImageBox(A.triggerEnum, "Truck interaction enum", { fit: "contain" })]),
              column({ width: fill, height: fill, gap: 8 }, [Evidence("적재칸 탑승 상태 검증"), ImageBox(A.cargoRide, "Cargo seat riding screenshot", { fit: "contain" })]),
            ],
          ),
        ],
      ),
    ],
  ),
]);

// 06 Cargo collision problem solving
Slide([
  column(
    { width: fill, height: hug, gap: 12 },
    [
      Eyebrow("PROBLEM SOLVING 01", C.rust),
      Title("적재칸을 자유 이동 공간으로 만들자, 캐릭터 캡슐이 트럭을 밀어내는 문제가 생겼습니다"),
      Body("캐릭터 캡슐이 차량 PhysicsAsset을 지속적으로 밀어 물리 연산이 불안정해지는 문제였습니다. Collision Profile을 분리해 이동 공간은 막되 차량 본체로 물리 힘이 전달되지 않도록 정리했습니다.", wrap(1420)),
    ],
  ),
  grid(
    { width: fill, height: fill, columns: [fr(1), fr(1), fr(0.9)], columnGap: 24 },
    [
      column({ width: fill, height: fill, gap: 8 }, [Evidence("Collision Profile 분리 코드"), ImageBox(A.cargoBoxesCode, "Cargo collision boxes code", { fit: "contain" })]),
      column({ width: fill, height: fill, gap: 8 }, [Evidence("적재칸 이동 범위 검증"), ImageBox(A.cargoBoxesView, "Cargo collision boxes view", { fit: "cover" })]),
      column(
        { width: fill, height: fill, gap: 18 },
        [
          Card("원인", "캡슐이 차량 물리 바디를 계속 밀어 물리 연산이 불안정해짐", C.rust),
          Card("해결", "적재칸 바닥/벽을 별도 BoxComponent로 만들고 Pawn만 막도록 분리", C.amber),
          Card("현재 코드", "`QueryOnly` + `ECC_Pawn Block`으로 이동 제약은 유지하고, 트럭 본체에 불필요한 Physics Impulse가 전달되지 않게 정리", C.moss),
        ],
      ),
    ],
  ),
]);

// 07 Cargo visual design
Slide([
  grid(
    { width: fill, height: fill, columns: [fr(1.08), fr(0.92)], columnGap: 44 },
    [
      column(
        { width: fill, height: fill, gap: 22 },
        [
          Eyebrow("SYSTEM 03", C.amber),
          Title("아이템 적재는 런타임 Spawn 대신 미리 배치한 슬롯을 갱신합니다"),
          Body("적재 시점마다 Actor나 Mesh를 새로 생성하면 위치 보정, 수명 관리, 프레임 안정성이 모두 흔들릴 수 있습니다. 그래서 종류별 슬롯을 미리 배치하고 상태 변화 때 표시 여부만 갱신하는 방식으로 바꾸었습니다.", wrap(820)),
          row(
            { width: fill, height: hug, gap: 16, align: "center" },
            [
              Step("처음", "동적 Spawn", "적재 때마다 메시를 생성"),
              Arrow(),
              Step("변경", "Pre-placed Slot", "Ammo/Fuel/MedKit 슬롯을 미리 배치"),
              Arrow(),
              Step("결과", "Frame 안정화", "상태 갱신만 수행해 시각 표현 동기화"),
            ],
          ),
          Card("최적화 효과", "런타임 Actor Spawn 비용을 제거해 순간 Frame Drop 위험을 낮추고, 반복 생성/파괴로 생기는 메모리 오버헤드와 GC 부담을 줄였습니다.", C.amber),
          Card("코드 근거", "ATruck 생성자에서 AmmoSlot, FuelSlot, MedKitSlot, MountedAmmoSlot 컴포넌트를 만들고 BeginPlay에서 숨김 처리한 뒤 적재 상태에 따라 노출합니다.", C.moss),
        ],
      ),
      column(
        { width: fill, height: fill, gap: 14 },
        [
          ImageBox(A.truckView, "Truck cargo gameplay", { fit: "cover" }),
          Caption("동적 생성 대신 에디터 배치 슬롯을 덮어쓰는 방식으로 적재 피드백을 안정화"),
        ],
      ),
    ],
  ),
]);

// 08 Mounted weapon component structure
Slide([
  grid(
    { width: fill, height: fill, columns: [fr(0.96), fr(1.04)], columnGap: 42 },
    [
      column(
        { width: fill, height: fill, gap: 22 },
        [
          Eyebrow("SYSTEM 04", C.blue),
          Title("거치형 기관총은 카메라, 축, 총구를 분리해서 조준감을 만들었습니다"),
          Body("기관총을 단순히 트럭 위에 붙이는 데서 끝내지 않고, 사용자가 보는 방향과 총구 발사 방향이 자연스럽게 이어지도록 컴포넌트 구조를 나눴습니다.", wrap(760)),
          Card(
            "구조",
            column(
              { width: fill, height: hug, gap: 10 },
              [
                Bullet("YawPivot", "좌우 회전만 담당"),
                Bullet("PitchPivot", "상하 회전과 카메라 붐 기준"),
                Bullet("MuzzlePoint", "블루프린트에서 총구 위치 조정"),
                Bullet("CameraPoint", "기관총 조준 시점 제공"),
              ],
            ),
            C.blue,
          ),
        ],
      ),
      column(
        { width: fill, height: fill, gap: 14 },
        [
          Evidence("거치형 기관총 컴포넌트 구조"),
          ImageBox(A.mountedCtor, "Mounted machine gun constructor code", { fit: "contain", height: fixed(350) }),
          ImageBox(A.mountedView, "Mounted machine gun gameplay", { fit: "cover" }),
        ],
      ),
    ],
  ),
]);

// 09 Aim and fire correction
Slide([
  grid(
    { width: fill, height: fill, columns: [fr(1.05), fr(0.95)], columnGap: 42 },
    [
      column(
        { width: fill, height: fill, gap: 20 },
        [
          Eyebrow("PROBLEM SOLVING 02", C.blue),
          Title("총알이 트럭을 맞거나 조준선과 어긋나는 문제를 단계적으로 고쳤습니다"),
          Body("카메라가 보는 방향, 총구의 실제 위치, 트럭과 사용자의 충돌 판정이 서로 어긋나면 총알이 트럭을 맞거나 조준선 밖으로 튀는 문제가 발생합니다. 화면 기준 조준과 월드 좌표 발사를 분리해 보정했습니다.", wrap(820)),
          grid(
            { width: fill, height: hug, columns: [fr(1), fr(1)], columnGap: 18, rowGap: 18 },
            [
              Card("1. 카메라 기준 조준", "카메라 위치에서 LineTrace로 목표 지점 계산", C.amber),
              Card("2. World Transform 보정", "MuzzlePoint의 World Transform에서 목표 지점까지 다시 검사해 막힌 지점 보정", C.moss),
              Card("3. 충돌 제외", "기관총, 사용자, 현재 트럭을 Trace/Projectile에서 무시", C.rust),
              Card("4. 발사체 재사용", "ObjectPool이 있으면 풀에서 꺼내고 없으면 SpawnActor fallback", C.blue),
            ],
          ),
        ],
      ),
      column(
        { width: fill, height: fill, gap: 14 },
        [
          Evidence("Camera Trace + Muzzle 보정 코드"),
          ImageBox(A.mountedAimCode, "Mounted gun aim trace code", { fit: "contain" }),
        ],
      ),
    ],
  ),
]);

// 10 Character control integration
Slide([
  grid(
    { width: fill, height: fill, columns: [fr(0.96), fr(1.04)], columnGap: 44 },
    [
      column(
        { width: fill, height: fill, gap: 20 },
        [
          Eyebrow("INTEGRATION", C.moss),
          Title("트럭에 타는 순간, 조작 대상과 캐릭터 표현이 동시에 바뀌어야 했습니다"),
          Body("트럭 조작은 가능하지만 캐릭터 표현이 운전석으로 따라오지 않는 상태 전환 문제가 있었습니다. 원인은 탑승 순간 Possess 대상이 바뀌며 `IsLocallyControlled` 흐름이 달라진 것이었습니다.", wrap(800)),
          Card("해결 방식", "운전석 탑승 호출 시 캐릭터를 DriverSeatPoint에 부착하고, 트럭에 부착된 캐릭터는 다른 플레이어 처리 코드가 잘못 개입하지 않도록 분기했습니다.", C.amber),
          Card("카메라 좌표 처리", "우클릭 줌과 크로스헤어 발사 보정도 같은 맥락에서, 화면 중앙을 `DeprojectScreenPositionToWorld`로 변환해 UI 조준점과 실제 발사 방향을 맞췄습니다.", C.blue),
        ],
      ),
      column(
        { width: fill, height: fill, gap: 14 },
        [
          ImageBox(A.sideTruck, "Driver and truck integration screenshot", { fit: "cover" }),
          row(
            { width: fill, height: hug, gap: 16 },
            [
              Card("상태 전환 분석", "문제 원인을 ‘컨트롤 대상 변경’까지 추적", C.moss),
              Card("면접 포인트", "Possess, Attach, Animation, Local Control 흐름 설명 가능", C.rust),
            ],
          ),
        ],
      ),
    ],
  ),
]);

// 11 Stage2 sketch
Slide([
  grid(
    { width: fill, height: fill, columns: [fr(1.05), fr(0.95)], columnGap: 42 },
    [
      column(
        { width: fill, height: fill, gap: 20 },
        [
          Eyebrow("SYSTEM 05", C.rust),
          Title("Stage2는 손으로 그린 Entry / Exit / Trigger 구조에서 출발했습니다"),
          Body("트럭이 다음 타일 트리거를 밟으면, 현재 타일의 Exit 위치에 다음 타일의 Entry가 맞물리도록 설계했습니다. 손으로 정리한 연결 규칙을 TileMarker와 TileManager 책임으로 분리했습니다.", wrap(800)),
          row(
            { width: fill, height: hug, gap: 16, align: "center" },
            [
              Step("TileMarker", "Entry Arrow", "타일의 시작 기준점"),
              Arrow(),
              Step("Trigger", "Next Tile Trigger", "트럭 진입 시 이벤트 발생"),
              Arrow(),
              Step("TileManager", "Exit → Entry", "다음 타일 위치 계산"),
            ],
          ),
          Card("구현 책임", "TileMarker는 타일 내부 기준점을 제공하고, TileManager는 어떤 타일을 언제 활성화할지 결정하도록 책임을 나눴습니다.", C.amber),
        ],
      ),
      column(
        { width: fill, height: fill, gap: 12 },
        [
          Evidence("Entry / Exit / Trigger 연결 설계"),
          ImageBox(A.stageSketch, "Stage2 tile hand sketch", { fit: "contain", bg: "#F6F3EA" }),
        ],
      ),
    ],
  ),
]);

// 12 Stage2 implementation
Slide([
  column(
    { width: fill, height: hug, gap: 12 },
    [
      Eyebrow("SYSTEM 05 / IMPLEMENTATION", C.rust),
      Title("비동기 로드의 빈틈을 ActiveTiles와 초기화 단계로 관리했습니다"),
      Body("비동기 레벨 스트리밍에서는 로드 요청 직후 타일 내부 Actor나 Marker를 바로 참조할 수 없습니다. 그래서 로드 요청과 Marker 확보를 분리하고, 초기화 확정 단계를 별도로 두었습니다.", wrap(1420)),
    ],
  ),
  grid(
    { width: fill, height: fill, columns: [fr(1.08), fr(1.08), fr(0.84)], columnGap: 24 },
    [
      column({ width: fill, height: hug, gap: 8 }, [Evidence("TileMarker 구성"), ImageBox(A.tileMarkerCode, "TileMarker code", { fit: "contain", height: fixed(330), bg: "#1F1F1F" })]),
      column({ width: fill, height: hug, gap: 8 }, [Evidence("ActiveTiles 메타데이터"), ImageBox(A.activeTilesCode, "Active tiles code", { fit: "contain", height: fixed(330), bg: "#1F1F1F" })]),
      column(
        { width: fill, height: fill, gap: 16 },
        [
          Card("1. 요청", "ULevelStreamingDynamic으로 타일 레벨 로드 요청", C.amber),
          Card("2. 보류", "ActiveTiles에 SourceLevel, StreamingLevel, Transform 저장", C.moss),
          Card("3. 확정", "Tick에서 TryFinalizeLoadedTiles로 Marker 확보", C.blue),
          Card("4. 연결", "Trigger 이벤트가 들어오면 다음 SpawnTransform 계산", C.rust),
        ],
      ),
    ],
  ),
]);

// 13 Stage2 optimization thinking
Slide([
  grid(
    { width: fill, height: fill, columns: [fr(1.05), fr(0.95)], columnGap: 42 },
    [
      column(
        { width: fill, height: fill, gap: 20 },
        [
          Eyebrow("ITERATION", C.amber),
          Title("Frame Drop를 줄이기 위해\n타일 로드와 재사용 시점을 분리했습니다"),
          Body("트리거를 밟는 순간 다음 맵을 로드하면 스트리밍 비용이 플레이 중간에 발생합니다. Stage2 진입 시 타일 풀을 선로드하고, 지나간 타일은 삭제 대신 재배치해 런타임 비용을 분산했습니다.", wrap(820)),
          grid(
            { width: fill, height: hug, columns: [fr(1), fr(1)], columnGap: 18, rowGap: 18 },
            [
              Card("성능 저하 인식", "Trigger-time Load → 순간 Frame Drop 가능성", C.rust),
              Card("선로드", "Stage2 진입 시 `PreloadedTilesPerType` 기준으로 TilePool 구성", C.amber),
              Card("재사용", "지나간 타일 삭제 대신 PoolParkingTransform으로 되돌려 재배치", C.moss),
              Card("Low-level 관점", "FStage2LoadedTile처럼 포인터, FTransform, bool 플래그가 섞인 구조는 sizeof, 필드 순서, bit packing을 기준으로 패딩/캐시 효율을 검토", C.blue),
            ],
          ),
        ],
      ),
      column(
        { width: fill, height: fill, gap: 14 },
        [
          ImageBox(A.stageOverview, "Stage2 map overview", { height: fixed(360), fit: "cover" }),
          ImageBox(A.stageFog, "Stage2 fog gameplay", { fit: "cover" }),
        ],
      ),
    ],
  ),
]);

// 14 Closing
Slide([
  grid(
    { width: fill, height: fill, columns: [fr(1), fr(1)], columnGap: 54 },
    [
      column(
        { width: fill, height: fill, gap: 22 },
        [
          Eyebrow("CLOSING", C.amber),
          Title("제가 보여주고 싶은 강점은\n기능 구현보다 구조를 끝까지 연결하는 태도입니다"),
          Body("이 프로젝트에서 저는 파밍, 트럭, 적재, 거치총, 스테이지 전환이 하나의 플레이 경험으로 이어지도록 시스템의 책임을 나누고, 문제가 생길 때마다 구조를 다시 잡았습니다.", wrap(820)),
          row(
            { width: fill, height: hug, gap: 18 },
            [
              Card("역할", "Gameplay 구조 설계", C.amber),
              Card("강점", "문제 원인 추적과 재설계", C.rust),
              Card("태도", "문제 원인과 설계 선택을 코드로 설명 가능", C.blue),
            ],
          ),
        ],
      ),
      column(
        { width: fill, height: fill, gap: 18 },
        [
          Card(
            "면접에서 설명 가능한 코드",
            column(
              { width: fill, height: hug, gap: 8 },
              [
                Small("ATruck: 상호작용 트리거, 적재 슬롯, 탑승/하차, 충돌 분리"),
                Small("AMountedMachineGun: 조준 보정, 발사체 풀링, 반동/탄피 피드백"),
                Small("AStage2TileManager: TileMarker 이벤트, ActiveTiles, TilePool, 비동기 로드 확정"),
              ],
            ),
            C.moss,
          ),
          ImageBox(A.truckStagePlay, "Truck in stage 2 gameplay", { fit: "cover" }),
        ],
      ),
    ],
  ),
]);

const pptxBlob = await PresentationFile.exportPptx(presentation);
await pptxBlob.save("output/output.pptx");

const previewDir = path.resolve("scratch", "previews");
fs.mkdirSync(previewDir, { recursive: true });
for (const file of fs.readdirSync(previewDir)) {
  if (file.endsWith(".png")) {
    fs.rmSync(path.join(previewDir, file));
  }
}
for (let index = 0; index < presentation.slides.items.length; index += 1) {
  const slide = presentation.slides.items[index];
  const pngBlob = await slide.export({ format: "png" });
  const pngBuffer = Buffer.from(await pngBlob.arrayBuffer());
  fs.writeFileSync(path.join(previewDir, `slide-${String(index + 1).padStart(2, "0")}.png`), pngBuffer);
}

const layoutDir = path.resolve("scratch", "layouts");
fs.mkdirSync(layoutDir, { recursive: true });
presentation.slides.items.forEach((slide, index) => {
  fs.writeFileSync(
    path.join(layoutDir, `slide-${String(index + 1).padStart(2, "0")}.layout.json`),
    JSON.stringify(slide.toSnapshot(), null, 2),
    "utf8",
  );
});

console.log(JSON.stringify({
  pptx: path.resolve("output", "output.pptx"),
  previews: previewDir,
  layouts: layoutDir,
  slides: presentation.slides.items.length,
}, null, 2));
