---
title: "Agentic AI 프로그래밍 실습 가이드"
subtitle: "OpenAI API + Python + Streamlit 입문"
author: "교양 AI 수업"
date: "2026"
documentclass: article
papersize: a4
fontsize: 11pt
geometry: margin=15mm
mainfont: "NanumGothic"
CJKmainfont: "NanumGothic"
monofont: "D2Coding"
monofontoptions:
  - Scale=0.85
header-includes:
  - \usepackage{kotex}
  - \usepackage{fancyhdr}
  - \pagestyle{fancy}
  - \fancyhf{}
  - \fancyhead[L]{Agentic AI 프로그래밍 실습 가이드}
  - \fancyfoot[C]{\thepage}
  - \usepackage{xcolor}
  - \usepackage{listings}
  - \lstset{basicstyle=\ttfamily\small, breaklines=true, frame=single, backgroundcolor=\color{gray!10}}
---

\newpage

# 이 가이드의 목적과 구성

이 가이드는 파이썬 문법을 몰라도 OpenAI API를 활용한 나만의 **Agentic AI 챗봇**을 만들 수 있도록 안내합니다. 순서대로 따라 하면 다음 결과물을 얻을 수 있습니다.

- 웹 브라우저에서 동작하는 나만의 AI 챗봇 화면
- 로컬 문서(PDF, TXT 등)와 URL을 참고 자료로 활용하는 AI
- ChatGPT에게 새 기능을 요청해 반복적으로 개선하는 워크플로

**구성 순서**

| 장 | 내용 |
|---|---|
| 1장 | 기본 .py 프레임 코드 및 구조 해설 |
| 2장 | Python 설치 방법 |
| 3장 | 편집기(메모장, VS Code) 사용법 |
| 4장 | OpenAI API 키 발급 및 .env 파일 관리 |
| 5장 | Windows Terminal 실행법 및 가상환경(.venv) 사용법 |

\newpage

---

# 1장. 기본 .py 프레임 코드

## 1.1 이 파일이 하는 일

아래 `agent_base.py`는 여러분이 자신만의 AI를 만들기 위한 **뼈대 코드**입니다. 이 코드를 ChatGPT 대화창에 첨부한 뒤 "이 코드를 기반으로 〈내가 원하는 기능〉을 수행하는 AI를 만들어줘"라고 요청하면, ChatGPT가 이 구조를 유지한 채 기능을 추가해 줍니다.

## 1.2 프로젝트 폴더 구조

코드를 실행하기 전에 아래와 같은 폴더 구조를 먼저 만들어 두십시오. 폴더 이름은 영문으로 짓는 것을 권장합니다.

```
my_agent/               <- 프로젝트 최상위 폴더 (이름은 자유롭게)
  |
  |-- agent_base.py     <- 메인 파이썬 코드 파일
  |-- .env              <- API 키를 보관하는 파일 (절대 공유 금지)
  |-- docs/             <- RAG용 참고 문서를 넣는 폴더 (선택)
  |     |-- sample.txt
  |     |-- reference.pdf
  |
  `-- .venv/            <- 가상환경 폴더 (자동 생성됨, 직접 수정 금지)
```

> **주의**: `.env` 파일은 절대로 타인에게 보내거나 온라인에 올리지 마십시오. API 키가 유출되면 요금이 청구될 수 있습니다.

## 1.3 agent_base.py 전체 코드

아래 코드를 VS Code 또는 메모장에 붙여 넣고, `my_agent` 폴더 안에 `agent_base.py`라는 이름으로 저장하십시오.

```python
# =============================================================
# agent_base.py  |  Agentic AI 기본 프레임
# 목적: OpenAI API를 활용한 멀티턴 챗봇 웹앱 뼈대
# 실행: streamlit run agent_base.py
# =============================================================

# ── 필수 라이브러리 불러오기 ──────────────────────────────────
import os                          # 운영체제 경로·환경변수 접근
import requests                    # URL에서 웹 페이지 내용 가져오기
from pathlib import Path           # 파일 경로를 다루는 도구

import streamlit as st             # 웹 UI를 만드는 라이브러리
from openai import OpenAI          # OpenAI API 클라이언트
from dotenv import load_dotenv     # .env 파일에서 환경변수 로드

# ── .env 파일 로드 (API 키를 읽어 옴) ────────────────────────
load_dotenv()                      # 현재 폴더의 .env 파일을 자동으로 읽음
client = OpenAI(
    api_key=os.getenv("OPENAI_API_KEY")   # .env 에 저장한 키를 가져옴
)

# =============================================================
# [학생 설정 영역 A]  페르소나(Persona)와 역할 지시문
# ▶ 이 부분의 따옴표 안 텍스트를 원하는 내용으로 수정하세요.
# =============================================================
SYSTEM_PROMPT = """
당신은 대학생의 학습을 돕는 친절한 AI 튜터입니다.
사용자가 질문하면 핵심을 먼저 설명하고, 이어서 예시를 들어줍니다.
전문 용어는 반드시 쉬운 말로 풀어서 설명하십시오.
답변은 항상 한국어로 작성합니다.
"""
# ↑ 역할 설명을 원하는 내용으로 자유롭게 바꾸세요.

# =============================================================
# [학생 설정 영역 B]  Few-shot 예시 메시지
# ▶ AI가 어떤 방식으로 답변하기를 원하는지 예시를 보여줍니다.
#    assistant 예시를 추가·수정해서 원하는 답변 스타일을 유도하세요.
# =============================================================
FEW_SHOT_EXAMPLES = [
    {
        "role": "user",
        "content": "머신러닝이 뭐야?"
    },
    {
        "role": "assistant",
        "content": (
            "**핵심 설명**: 머신러닝은 컴퓨터가 데이터를 보고 스스로 규칙을 찾아내는 기술입니다.\n\n"
            "**예시**: 수천 장의 고양이 사진을 보여주면, 컴퓨터가 '귀가 뾰족하고 눈이 크면 고양이'라는 "
            "규칙을 스스로 만들어냅니다.\n\n"
            "더 궁금한 점이 있으면 질문해 주세요!"
        )
    },
]
# ↑ 예시 쌍(user/assistant)을 추가하거나 내용을 바꿔 원하는 스타일을 지정하세요.

# =============================================================
# 참고 문서 불러오기 함수
# ▶ docs/ 폴더에 넣은 텍스트 파일의 내용을 읽어서 AI에게 전달합니다.
# =============================================================
def load_local_docs(docs_folder: str = "docs") -> str:
    """
    docs/ 폴더 안의 .txt 파일을 모두 읽어 하나의 문자열로 합칩니다.
    AI는 이 내용을 참고 자료로 활용합니다.
    """
    docs_path = Path(docs_folder)
    if not docs_path.exists():           # docs 폴더가 없으면 빈 문자열 반환
        return ""

    combined = []
    for txt_file in docs_path.glob("*.txt"):   # .txt 파일만 읽음
        try:
            text = txt_file.read_text(encoding="utf-8")
            combined.append(f"[문서: {txt_file.name}]\n{text}")
        except Exception:
            pass                         # 읽기 실패 시 조용히 넘어감

    return "\n\n".join(combined)         # 여러 파일 내용을 이어 붙임


# =============================================================
# 참고 URL 불러오기 함수
# ▶ 사용자가 입력한 URL의 웹 페이지 텍스트를 가져옵니다.
# =============================================================
def fetch_url_content(url: str) -> str:
    """
    주어진 URL에 접속해 HTML을 가져온 뒤 순수 텍스트를 반환합니다.
    HTML 태그는 제거하고 텍스트만 추출합니다.
    """
    try:
        response = requests.get(url, timeout=10)  # 10초 안에 응답 없으면 포기
        response.raise_for_status()               # 오류 상태코드면 예외 발생
        # 간단한 태그 제거 (beautifulsoup 없이 처리)
        import re
        text = re.sub(r"<[^>]+>", " ", response.text)   # HTML 태그 제거
        text = re.sub(r"\s+", " ", text).strip()         # 연속 공백 정리
        return text[:3000]               # 너무 길면 앞 3000자만 사용
    except Exception as e:
        return f"[URL 로드 실패: {e}]"


# =============================================================
# OpenAI API 호출 함수
# ▶ 대화 이력(messages)을 전달하고 AI의 답변을 받아옵니다.
# =============================================================
def get_ai_response(messages: list) -> str:
    """
    OpenAI ChatCompletion API를 호출합니다.
    messages: 지금까지의 대화 전체 목록 (system, user, assistant 포함)
    반환값: AI가 생성한 답변 문자열
    """
    response = client.chat.completions.create(
        model="gpt-4o-mini",             # 사용할 모델 (변경 가능)
        messages=messages,               # 전체 대화 이력 전달
        temperature=0.7,                 # 창의성 수준 (0=일정, 1=창의적)
        max_tokens=1500,                 # 답변 최대 길이 (토큰 단위)
    )
    return response.choices[0].message.content   # 답변 텍스트만 추출


# =============================================================
# Streamlit 웹 UI 구성
# ▶ 아래부터는 웹 화면에 표시되는 요소를 정의합니다.
# =============================================================

# 브라우저 탭에 표시될 제목과 아이콘
st.set_page_config(page_title="나의 AI 에이전트", page_icon="🤖")

# 웹 페이지 제목
st.title("🤖 나의 Agentic AI 챗봇")
st.caption("OpenAI API 기반 | Streamlit UI")

# ── 사이드바: 참고 자료 설정 ──────────────────────────────────
with st.sidebar:
    st.header("📂 참고 자료 설정")

    # 로컬 문서 불러오기 체크박스
    use_docs = st.checkbox("로컬 docs/ 폴더 문서 참고", value=False)

    # 참고할 URL 입력창 (여러 개 줄바꿈으로 구분)
    url_input = st.text_area(
        "참고할 URL (여러 개면 줄바꿈으로 구분)",
        placeholder="https://example.com\nhttps://another.com",
        height=100,
    )

    st.markdown("---")
    # 대화 초기화 버튼
    if st.button("🗑️ 대화 초기화"):
        st.session_state.messages = []   # 대화 이력 비우기
        st.rerun()                        # 화면 새로 고침

# ── 세션 상태 초기화 ──────────────────────────────────────────
# st.session_state: 새로 고침해도 데이터가 유지되는 저장소
if "messages" not in st.session_state:
    st.session_state.messages = []       # 대화 이력을 담는 빈 목록

# ── 지금까지의 대화 화면에 표시 ──────────────────────────────
for msg in st.session_state.messages:
    if msg["role"] == "user":
        st.chat_message("user").write(msg["content"])
    elif msg["role"] == "assistant":
        st.chat_message("assistant").write(msg["content"])

# ── 사용자 입력창 ─────────────────────────────────────────────
user_input = st.chat_input("메시지를 입력하세요…")

if user_input:
    # 사용자 메시지를 화면에 즉시 표시
    st.chat_message("user").write(user_input)

    # ── API에 보낼 messages 목록 조립 ──────────────────────────
    # 1) 시스템 프롬프트 (페르소나 지시문)
    system_content = SYSTEM_PROMPT

    # 2) 로컬 문서 내용 추가 (체크박스가 켜진 경우)
    if use_docs:
        doc_text = load_local_docs("docs")
        if doc_text:
            system_content += f"\n\n[참고 문서 내용]\n{doc_text}"

    # 3) URL 내용 추가 (URL이 입력된 경우)
    if url_input.strip():
        for url in url_input.strip().splitlines():
            url = url.strip()
            if url:
                fetched = fetch_url_content(url)
                system_content += f"\n\n[참고 URL: {url}]\n{fetched}"

    # 4) 전체 messages 목록: system → few-shot → 대화 이력 → 현재 질문
    messages_to_send = (
        [{"role": "system", "content": system_content}]
        + FEW_SHOT_EXAMPLES               # few-shot 예시 삽입
        + st.session_state.messages       # 지금까지의 대화 이력
        + [{"role": "user", "content": user_input}]   # 현재 질문
    )

    # 5) AI 답변 받기 (로딩 스피너 표시)
    with st.spinner("AI가 생각하는 중…"):
        answer = get_ai_response(messages_to_send)

    # 6) 답변을 화면에 표시
    st.chat_message("assistant").write(answer)

    # 7) 대화 이력에 저장 (다음 턴에 context로 활용)
    st.session_state.messages.append({"role": "user",      "content": user_input})
    st.session_state.messages.append({"role": "assistant", "content": answer})
```

## 1.4 필수 라이브러리 설치 명령

이 파일을 실행하기 전에 Windows Terminal에서 아래 명령을 한 번만 실행하십시오 (가상환경 활성화 후).

```
pip install openai streamlit python-dotenv requests
```

## 1.5 실행 명령

```
streamlit run agent_base.py
```

실행하면 자동으로 웹 브라우저가 열리고 챗봇 화면이 나타납니다.

## 1.6 학생이 수정해야 할 부분 요약

| 위치 | 변수명 | 수정 내용 |
|---|---|---|
| 설정 영역 A | `SYSTEM_PROMPT` | AI의 역할·말투·응답 규칙 |
| 설정 영역 B | `FEW_SHOT_EXAMPLES` | 원하는 답변 형식의 예시 대화 |
| API 호출 함수 | `model=` | 사용할 GPT 모델명 |
| 페이지 설정 | `page_title=` | 브라우저 탭 제목 |
| `st.title()` | 따옴표 안 문자열 | 웹 페이지 제목 |

\newpage

---

# 2장. Python 설치 방법

## 2.1 Python이 필요한 이유

`agent_base.py`는 Python으로 작성된 프로그램입니다. Python이 컴퓨터에 설치되어 있어야 이 파일을 실행할 수 있습니다.

## 2.2 설치 절차

**단계 1. 공식 사이트 접속**

웹 브라우저에서 아래 주소로 이동합니다.

```
https://www.python.org/downloads/
```

**단계 2. 설치 파일 다운로드**

페이지 상단의 노란색 `Download Python 3.x.x` 버튼을 클릭합니다. Windows용 설치 파일(`.exe`)이 자동으로 다운로드됩니다.

**단계 3. 설치 실행 — 중요 옵션 확인**

다운로드된 `.exe` 파일을 더블클릭합니다. 설치 창이 열리면 **반드시** 아래 항목을 체크하십시오.

> ✅ **Add Python to PATH** (화면 하단에 위치)

이 옵션을 체크하지 않으면 Windows Terminal에서 `python` 명령이 인식되지 않습니다.

체크 후 `Install Now`를 클릭합니다.

**단계 4. 설치 확인**

Windows Terminal(또는 명령 프롬프트)을 열고 아래 명령을 입력합니다.

```
python --version
```

`Python 3.x.x` 와 같이 버전 번호가 출력되면 설치가 완료된 것입니다.

## 2.3 Python 버전 권장 사항

- **Python 3.10 이상**을 권장합니다.
- Python 2.x 버전은 지원이 종료되었으므로 설치하지 마십시오.

\newpage

---

# 3장. 편집기 사용법

## 3.1 편집기가 필요한 이유

ChatGPT가 생성해 준 `.py` 코드를 복사해서 파일로 저장해야 합니다. 이 작업에 **텍스트 편집기**가 필요합니다. 여기서는 메모장과 VS Code 두 가지를 안내합니다.

## 3.2 메모장 사용법 (가장 간단한 방법)

메모장은 Windows에 기본 설치되어 있습니다.

**파일 저장 절차**

1. 시작 메뉴에서 `메모장`을 검색해 실행합니다.
2. ChatGPT 대화창에서 생성된 코드 전체를 `Ctrl+A`로 선택 후 `Ctrl+C`로 복사합니다.
3. 메모장 창에 `Ctrl+V`로 붙여 넣습니다.
4. `파일 → 다른 이름으로 저장`을 선택합니다.
5. 아래 설정을 반드시 확인하고 저장합니다.

| 항목 | 설정값 |
|---|---|
| 저장 위치 | `my_agent` 폴더 |
| 파일 이름 | `agent_base.py` (확장자 포함) |
| 파일 형식 | **모든 파일 (\*.\*)** 선택 |
| 인코딩 | **UTF-8** 선택 |

> ⚠️ 파일 형식을 "텍스트 문서"로 두면 `agent_base.py.txt`로 저장되어 실행되지 않습니다. 반드시 **모든 파일**로 변경하십시오.

## 3.3 VS Code 설치 및 사용법 (권장)

VS Code는 코드 편집에 특화된 무료 편집기로, 코드 색상 강조, 오류 표시 등 편리한 기능을 제공합니다.

**설치 방법**

1. 아래 주소에서 설치 파일을 다운로드합니다.
   ```
   https://code.visualstudio.com/
   ```
2. 다운로드된 `.exe` 파일을 실행하고 기본 설정으로 설치합니다.
3. 설치 중 `PATH에 추가` 옵션이 있으면 체크합니다.

**파일 저장 절차**

1. VS Code를 실행합니다.
2. `파일 → 폴더 열기`에서 `my_agent` 폴더를 선택합니다.
3. 왼쪽 탐색기에서 `새 파일` 아이콘을 클릭하고 `agent_base.py`를 입력합니다.
4. ChatGPT에서 복사한 코드를 오른쪽 편집 창에 `Ctrl+V`로 붙여 넣습니다.
5. `Ctrl+S`로 저장합니다.

**한국어 확장 설치 (선택)**

VS Code 왼쪽 사이드바의 확장(Extensions) 아이콘을 클릭하고 `Korean Language Pack`을 검색해 설치하면 메뉴가 한국어로 표시됩니다.

## 3.4 `.env` 파일 만들기

`.env` 파일은 API 키를 저장하는 특수 파일입니다. VS Code 또는 메모장으로 아래와 같이 만드십시오.

**내용 예시:**
```
OPENAI_API_KEY=sk-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
```

**저장 방법 (메모장 사용 시)**

- 파일 이름: `.env`
- 파일 형식: **모든 파일 (\*.\*)**
- 저장 위치: `my_agent` 폴더

> `.env`는 파일 이름 앞에 점(`.`)이 붙습니다. Windows 탐색기에서 숨김 파일로 표시될 수 있습니다.

\newpage

---

# 4장. OpenAI API 키 발급 및 관리

## 4.1 API 키란?

API 키는 OpenAI 서버에 접속할 때 사용하는 **개인 비밀번호**입니다. 이 키가 있어야 `agent_base.py`가 GPT 모델을 호출할 수 있습니다.

> ⚠️ API 키는 절대 타인에게 공유하거나 GitHub 등 온라인 저장소에 올리지 마십시오. 키가 유출되면 본인 계정으로 요금이 청구됩니다.

## 4.2 API 키 발급 절차

**단계 1. OpenAI 계정 생성**

아래 주소에서 계정을 만듭니다(이미 있으면 로그인).

```
https://platform.openai.com/signup
```

**단계 2. API 키 생성 페이지 이동**

로그인 후 아래 주소로 이동합니다.

```
https://platform.openai.com/api-keys
```

**단계 3. 새 키 생성**

1. `Create new secret key` 버튼을 클릭합니다.
2. 키 이름을 입력합니다 (예: `my-agent-key`).
3. `Create secret key`를 클릭합니다.
4. 생성된 키(`sk-...`)가 화면에 표시됩니다. **이 순간에만 전체 키를 볼 수 있으므로** 반드시 복사해 두십시오.

**단계 4. 크레딧 충전 (필요 시)**

무료 크레딧이 소진된 경우 `Billing` 메뉴에서 결제 수단을 등록하고 소액을 충전합니다. 학습용으로는 $5 정도면 충분합니다.

## 4.3 .env 파일에 키 저장하기

1. `my_agent` 폴더 안에 `.env` 파일을 만듭니다 (3장 3.4절 참고).
2. 아래 형식으로 키를 입력하고 저장합니다.

```
OPENAI_API_KEY=sk-여기에_발급받은_키를_붙여넣기
```

3. 등호(`=`) 앞뒤에 공백을 넣지 않도록 주의합니다.

## 4.4 .env 파일 관리 주의사항

- `.env` 파일은 `my_agent` 폴더 **최상위**에 위치해야 합니다.
- 파이썬 코드의 `load_dotenv()`가 같은 폴더의 `.env`를 자동으로 읽습니다.
- 과제 제출 시 `.env` 파일은 제출하지 않고 `.py` 파일만 제출합니다.
- API 키를 `.py` 코드 안에 직접 쓰지 마십시오. 코드가 유출될 경우 키도 함께 노출됩니다.

## 4.5 사용량 모니터링

발급받은 키의 사용량과 잔여 크레딧은 아래에서 확인할 수 있습니다.

```
https://platform.openai.com/usage
```

\newpage

---

# 5장. Windows Terminal 실행법 및 가상환경 사용법

## 5.1 Windows Terminal이란?

Windows Terminal은 명령어를 입력해 프로그램을 실행하는 텍스트 기반 도구입니다. `.py` 파일은 이중 클릭으로는 실행되지 않으므로 Windows Terminal을 사용해야 합니다.

## 5.2 Windows Terminal 열기

방법 1 (권장): 시작 메뉴에서 `Windows Terminal`을 검색해 실행합니다.

방법 2: 탐색기에서 `my_agent` 폴더를 연 상태에서, 주소창을 클릭하고 `wt`를 입력한 후 Enter를 누릅니다. 해당 폴더 위치에서 터미널이 바로 열립니다.

## 5.3 가상환경(.venv)이란? 그리고 왜 써야 하나?

**비유로 이해하기**

컴퓨터 전체에 라이브러리를 설치하면, 여러 프로젝트가 서로 다른 버전의 라이브러리를 요구할 때 충돌이 발생합니다. **가상환경**은 각 프로젝트만을 위한 격리된 Python 공간으로, 다른 프로젝트에 영향을 주지 않습니다.

마치 요리마다 별도의 조리 도구 세트를 갖추는 것과 같습니다.

**가상환경의 장점**

- 프로젝트마다 필요한 라이브러리를 독립적으로 관리
- 시스템 Python 환경을 오염시키지 않음
- 나중에 같은 프로젝트를 다른 컴퓨터에서 재현하기 쉬움

## 5.4 프로젝트 최초 설정 절차 (처음 한 번만)

아래 명령들을 Windows Terminal에서 **순서대로** 실행합니다.

**단계 1: 프로젝트 폴더로 이동**

```
cd C:\Users\사용자이름\Desktop\my_agent
```

> `사용자이름` 부분을 본인의 Windows 사용자 이름으로 바꾸십시오.  
> 폴더를 Desktop(바탕화면)이 아닌 다른 곳에 만들었다면 그 경로를 입력합니다.

**팁**: 탐색기에서 폴더 주소창의 경로를 복사한 뒤 `cd` 뒤에 붙여 넣어도 됩니다.

**단계 2: 가상환경 생성**

```
python -m venv .venv
```

이 명령을 실행하면 `my_agent` 폴더 안에 `.venv` 폴더가 자동으로 생성됩니다. **한 번만 실행**하면 됩니다.

**단계 3: 가상환경 활성화**

```
.venv\Scripts\activate
```

활성화되면 프롬프트 앞에 `(.venv)` 표시가 나타납니다.

```
(.venv) C:\Users\사용자이름\Desktop\my_agent>
```

**단계 4: 필수 라이브러리 설치**

```
pip install openai streamlit python-dotenv requests
```

인터넷에서 라이브러리를 내려받으므로 잠시 기다립니다. 역시 **한 번만 실행**하면 됩니다.

## 5.5 매번 실행할 때의 절차

프로젝트를 실행할 때마다 아래 두 단계만 수행합니다.

**단계 1: 가상환경 활성화**

```
cd C:\Users\사용자이름\Desktop\my_agent
.venv\Scripts\activate
```

**단계 2: Streamlit으로 실행**

```
streamlit run agent_base.py
```

잠시 후 웹 브라우저가 자동으로 열리고 챗봇 화면이 나타납니다. 브라우저가 열리지 않으면 터미널에 출력된 `http://localhost:8501` 주소를 직접 브라우저에 입력합니다.

## 5.6 실행 종료 방법

챗봇을 종료하려면 Windows Terminal에서 `Ctrl+C`를 누릅니다.

## 5.7 자주 발생하는 오류와 해결 방법

| 오류 메시지 | 원인 | 해결 방법 |
|---|---|---|
| `'python'은(는) 내부 또는 외부 명령...` | Python이 PATH에 없음 | Python을 재설치하면서 `Add to PATH` 체크 |
| `ModuleNotFoundError: No module named 'openai'` | 라이브러리 미설치 | 가상환경 활성화 후 `pip install openai` 재실행 |
| `AuthenticationError` | API 키 오류 | `.env` 파일의 키 값 확인 |
| `streamlit: command not found` | 가상환경 미활성화 | `.venv\Scripts\activate` 먼저 실행 |
| 스크립트 실행 보안 오류 | PowerShell 정책 문제 | 아래 명령 실행 후 재시도 |

PowerShell 보안 오류가 발생하는 경우:

```
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

## 5.8 전체 워크플로 요약

```
[처음 한 번만]
python -m venv .venv
.venv\Scripts\activate
pip install openai streamlit python-dotenv requests

[매번 실행 시]
.venv\Scripts\activate
streamlit run agent_base.py
```

\newpage

---

# 부록. ChatGPT에게 .py 수정 요청하는 방법

## 기능 추가 요청 예시

ChatGPT 대화창에 `agent_base.py` 전체 코드를 붙여 넣은 뒤 아래와 같이 요청합니다.

> "첨부한 코드를 기반으로, 사용자가 입력한 텍스트를 영어로 번역해주는 기능을 추가해줘. 번역 결과는 원문 아래에 표시되어야 해. 추가된 코드에는 한국어 주석을 꼭 달아줘. 그리고 이 코드를 실행하기 위해 추가로 설치해야 할 라이브러리가 있다면 pip install 명령도 함께 알려줘."

## 오류 수정 요청 예시

오류가 발생했을 때 오류 메시지 전체를 복사해서 아래와 같이 요청합니다.

> "아래 오류가 발생했어. 코드에서 어떤 부분을 수정해야 해?\n\n`[오류 메시지 붙여넣기]`"

## function calling 포함 요청 예시

> "첨부한 코드를 기반으로, 사용자가 도시 이름을 입력하면 현재 날씨를 알려주는 기능을 추가해줘. OpenWeatherMap API를 function calling으로 호출하는 방식으로 구현하고, 함수가 실행하는 내용을 한국어 주석으로 설명해줘."
