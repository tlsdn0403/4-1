---
title: "바이브코딩 실습 최소 가이드"
author: 송경모
date: 2026-04-15
organization: 한국공학대학교
category: Memo
version: 00
tags: [ AI, Artificial Intelligence, Codingm, Programming ]
keywords: [ Vibe Coding, 바이브코딩, Coding Agent ]
pdf-engine: xelatex
header-includes:
  - \usepackage{kotex}
  - \setmainhangulfont{NanumMyeongjo}

mainfont: "Times New Roman"
monofont: "Consolas"
fontsize: 11pt
geometry: margin=15mm
---

# 개요
요청 prompt: "대학교 교양 과목을 수강하는 학생들에게 OpenAI 플랫폼에서 바이브 코딩을 시도해볼 수 있는 과정을 안내하고 싶다. 개인 자격으로 가장 접근이 용이한 수준부터 시작해서 고급의 수준까지 다음과같은 내용이 담기도록 가이드를 .md 파일 서식으로 작성해달라 - 접근 절차( 인터페이스, 설치가 필요한 SW 또는 플러그인, 과금 수준) - 바이브 코딩 작업 들어가기 전에 명확히 해두어야 할 사항을 확정하는 방법( 프로그래밍 언어 및 각종 도구 지정, 과업의 목적과 구조 설계 등) - 구사 가능한 작업의 범위, 수준, 한계 - 작업 절차 안내 (프롬프트 예시, 첨부하는 md 파일의 구성과 md 파일에 담겨야 할 내용과 작성 원칙 예시, 디버깅 수정 검증 절차, 최종 개인 사용 또는 배포 시 유의 사항) - 가장 높은 단계의 작업인 harness engineering의 기본 절차에 대해서도 별도로 안내"
# ======OpenAI의 설명======
# OpenAI 기반 바이브 코딩(Vibe Coding) 실습 가이드

*대학교 교양 과목용 단계별 안내*

---

# 0. 개요

이 문서는 AI 비전공자를 대상으로, OpenAI 플랫폼을 활용한 **바이브 코딩(Vibe Coding)**을
가장 쉬운 수준부터 고급 수준(Agentic AI 및 Harness Engineering)까지 단계적으로 안내한다.

---

# 1. 접근 절차 (Access & Setup)

## 1.1 최소 진입 (Level 0: No-code)

* 인터페이스: ChatGPT 웹
* 필요 SW: 없음
* 계정: OpenAI 계정
* 과금:

  * Free: 제한적 사용
  * Plus: 실습 가능 수준

### 활용

* 코드 생성
* 간단한 수정
* 개념 학습

---

## 1.2 준개발 환경 (Level 1: Light Coding)

* 인터페이스:

  * ChatGPT + 로컬 실행
* 필요 SW:

  * Python (Windows 설치)
  * VS Code (권장)
* 플러그인:

  * Python extension

### 과금 구조

1. Plus Plan에서도 Codex 사용 가능

→  다만, 사용량 제한(quota 있음)이 있다. 대략 “주간 몇 번의 coding 세션 수준”, 초과 시 추가 크레딧 구매가 필요

* 가능
  * 코드 생성
  * Python 스크립트 작성
  * 간단한 agent 설계
  * 디버깅
* 제한(이런 제한을 풀려면 Pro요금제 상향)
  * 대형 프로젝트 (multi-file refactor)
  * 장시간 agent 실행
  * 반복적 자동화 실험

Codex는 별도 상품이 아니라 ChatGPT 유료 플랜(Plus, Pro, Business / Enterprise 등)에 포함된 기능이다


---

## 1.3 개발 환경 (Level 2: API 기반)

* 인터페이스:

  * Python + OpenAI API

이미 API key를 가지고 있다면 다음과 같은 식으로 모델을 "gpt-5.3-codex"로 설정하고 작업한다


```
from openai import OpenAI
client = OpenAI()

response = client.responses.create(
    model="gpt-5.3-codex",
    input=" PDF 파일을 읽고 요약해주는 python 코드를 작성해줘."
	print(response.output[0].content[0].text)
```


* 필요:

  * API Key 를 받아놓고 .env 파일(프로젝트 폴더 안에 위치)에 별도로 기록해놓아야 한다.
  * 프로젝트 폴더 안에 python 가상환경 .venv 폴더가 생성되어 있어야 한다.

* 과금: 

	* 이 방식은 토큰 사용량에 따라 별도 과금된다.

---

## 1.4 고급 환경 (Level 3: Agent / Harness)

* 인터페이스:

  * Python + Multi-agent 구조
  
* 필요:

  * 프레임워크 (LangChain 등 선택적)
  * 테스트 harness 구성

LangChain, LangGraph란 여러 회사의 모델에 통용될 수 있는, LLM을 보다 편리하게 다룰 수 있는 다양한 기능의 함수 라이브러리다. 


---

# 2. 작업 시작 전 필수 정의 사항

## 2.1 기술 스택 확정

* 언어: Python (권장)
* 실행 환경: Windows + Terminal
* API 사용 여부 결정

---

## 2.2 과업 정의 프레임워크

다음 4가지를 반드시 명확히 한다:

### (1) 목적 (Goal)

* 무엇을 만들 것인가
* 예: "PDF 요약 자동화 도구"

### (2) 입력 (Input)

* 텍스트 / 파일 / API 등

### (3) 출력 (Output)

* 텍스트 / JSON / 파일

### (4) 처리 구조 (Process)

* 단계별 처리 흐름

---

## 2.3 Persona 및 역할 정의

예:

* "너는 Python 데이터 엔지니어다"
* "너는 코드 리뷰 전문가다"

---

## 2.4 제약 조건 정의

* 실행 시간
* 비용 제한
* 정확도 요구 수준

---

# 3. 바이브 코딩의 범위 / 수준 / 한계

## 3.1 가능한 작업

### 기본

* 코드 생성
* 오류 수정
* 문서화

### 중급

* 파일 처리 자동화
* API 호출 시스템

### 고급

* Agent 구성
* 멀티 스텝 reasoning

---

## 3.2 한계

* 완전 자동 시스템 설계는 불안정
* 복잡한 상태 관리 어려움
* 장기 실행 작업에서 오류 발생 가능

---

## 3.3 위험 요소

* hallucination (잘못된 코드)
* dependency 충돌
* 보안 문제 (API key 노출)

---

# 4. 작업 절차 (Workflow)

## 4.1 기본 구조

1. 문제 정의
2. 프롬프트 설계
3. 코드 생성
4. 실행
5. 디버깅
6. 개선 반복

---

## 4.2 프롬프트 예시

```
You are a Python developer.

Task:
- Read a PDF file
- Extract text
- Summarize it

Requirements:
- Use PyMuPDF
- Output in bullet points
- Handle errors

Return:
- Complete Python script
```

---

## 4.3 프로젝트 폴더 구조

Level 1 에서는 다음과 같은 폴더 구조로 충분하다.

```
project/
 ├── main.py
 ├── utils/
 ├── data/
 ├── outputs/
 ├── prompts/
 └── README.md
```

---
만약 Level 2 이상 API key를 받아서 하는 작업일 경우 폴더 구조는 다음과 같이 .env (API Key 기록 파일)과 .venv 폴더(Python 실행 가상환경폴더)가 프로젝트 폴더 안에 포함되어 있어야 한다.

```
project/
 ├── .venv/          ← 필수 (실행 환경)
 ├── .env            ← 필수 (비밀키)
 ├── main.py
 ├── utils/
 ├── data/
 ├── outputs/
 ├── prompts/
 ├── requirements.txt
 └── README.md
```

## 4.4 MD 파일 작성 원칙

### 필수 포함 항목

* 목적
* 입력/출력 정의
* 실행 방법
* 예시

### 작성 규칙

* 명확성 (ambiguous 금지)
* 재현 가능성
* 최소 단위 설명

---

## 4.5 디버깅 절차

1. 오류 메시지 확인
2. AI에게 오류 전달
3. 수정 요청
4. 부분 테스트
5. 전체 실행

---

## 4.6 검증 방법

* 입력-출력 테스트
* edge case 테스트
* 반복 실행 안정성 확인

---

## 4.7 배포 시 유의 사항

* API key 환경변수 처리
* 로그 제거
* 비용 관리
* 라이선스 확인

---

# 5. Harness Engineering (최고 단계)

## 5.1 정의

Harness Engineering =
AI 시스템을 안정적으로 실행하기 위한 **실험/검증/통제 구조 설계**

---

## 5.2 기본 구조

```
User Input
   ↓
Task Decomposition
   ↓
Agent Execution
   ↓
Validation
   ↓
Retry / Correction
```

---

## 5.3 핵심 구성 요소

### (1) Task Decomposer

* 문제를 작은 단위로 분해

### (2) Executor

* 각 단계 실행

### (3) Validator

* 결과 검증

### (4) Controller

* 흐름 관리

---

## 5.4 예시 구조

```python
def run_pipeline(task):
    steps = decompose(task)

    results = []
    for step in steps:
        result = execute(step)

        if not validate(result):
            result = retry(step)

        results.append(result)

    return results
```

---

## 5.5 핵심 원칙

* deterministic control 확보
* 실패 대비 구조 설계
* 반복 실행 가능성
* 비용 관리

---

## 5.6 교육용 최소 구현

학생 수준에서는 다음까지만 요구:

* 단일 agent
* 단계 분리
* 간단한 validation

---

# 6. 단계별 학습 로드맵

## Level 0

* ChatGPT로 코드 생성

## Level 1

* Python 실행

## Level 2

* API 호출

## Level 3

* 자동화 스크립트

## Level 4

* Agent 구성

## Level 5

* Harness Engineering

---

# 7. 결론

바이브 코딩은
“코드를 직접 작성하는 행위”가 아니라
“AI와 협력하여 시스템을 설계하는 행위”이다.

초보자는:
→ ChatGPT 기반 실습부터 시작

중급자는:
→ API + Python

고급자는:
→ Agent + Harness 구조

이 순서로 발전하는 것이 가장 효율적이다.

---


# =====ChatGPT, CODEX에 대한 Claude의 설명=====
---
title: "바이브 코딩(Vibe Coding) 실습 가이드"
subtitle: "OpenAI 플랫폼 기반 | 입문부터 고급까지"
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
  - \usepackage{xcolor}
  - \usepackage{listings}
  - \lstset{basicstyle=\ttfamily\small, breaklines=true, frame=single, backgroundcolor=\color{gray!10}}
  - \pagestyle{fancy}
  - \fancyhf{}
  - \fancyhead[L]{바이브 코딩 실습 가이드}
  - \fancyfoot[C]{\thepage}
---

\newpage

# 이 가이드를 읽기 전에

**바이브 코딩(Vibe Coding)** 이란, 프로그래밍 언어 문법을 몰라도 자연어(한국어 또는 영어)로 AI에게 지시해 실제로 작동하는 코드를 만들어내는 작업 방식입니다. Andrej Karpathy가 2025년에 명명한 이 개념은 "코드를 작성하는 것이 아니라 코드가 무엇을 해야 하는지 대화하는 것"이라는 철학에 기반합니다.

이 가이드는 수강생의 기술 수준과 목표에 따라 **세 가지 레벨**로 구성되어 있습니다.

| 레벨 | 플랫폼 | 대상 |
|---|---|---|
| **Lv.1 입문** | ChatGPT 웹 브라우저 | 코딩 경험 전무 |
| **Lv.2 중급** | Codex CLI / VS Code + Copilot | 터미널 사용 가능 |
| **Lv.3 고급** | OpenAI API 직접 구성 | 구조적 프로젝트 설계 가능 |

---

\newpage

# 1장. 레벨별 접근 절차

## 1.1 Lv.1 --- ChatGPT 웹 인터페이스 (입문)

### 인터페이스

- 접속 주소: `https://chatgpt.com`
- 별도 소프트웨어 설치 불필요 (웹 브라우저만 있으면 됨)
- 생성된 코드를 복사해 메모장 또는 VS Code에 저장 후 실행

### 과금 수준

| 플랜 | 월 요금 | 바이브 코딩 적합성 |
|---|---|---|
| Free | 무료 | GPT-4o mini 사용 가능, 횟수 제한 있음 |
| Plus | \$20/월 | GPT-4o, o3 접근, 파일 업로드, Canvas 기능 |
| Pro | \$200/월 | o3-pro, 무제한 사용 (대형 프로젝트) |

학생 권장 플랜은 **Plus**입니다. Canvas 모드를 활용하면 코드를 대화창 옆에서 실시간으로 편집할 수 있어 바이브 코딩에 적합합니다.

### ChatGPT Canvas 활성화 방법

1. `chatgpt.com` 접속 후 로그인합니다.
2. 새 대화를 시작합니다.
3. 프롬프트 입력창 우측의 Canvas 아이콘을 클릭하거나, "Canvas로 코드 작성해줘"라고 입력합니다.
4. 코드가 우측 패널에 분리되어 표시됩니다. 특정 줄을 클릭해 수정을 요청할 수 있습니다.

---

## 1.2 Lv.2 --- Codex CLI (중급)

### 인터페이스

터미널에서 자연어로 코딩 작업을 지시하는 OpenAI 공식 CLI 도구입니다. 로컬 파일을 직접 읽고 수정할 수 있어 실제 프로젝트에 바로 적용됩니다.

### 설치 절차

사전 요구사항으로 Node.js 22 이상이 설치되어 있어야 합니다.

```
node --version

npm install -g @openai/codex

codex auth
```

설치 후 프로젝트 폴더에서 아래와 같이 실행합니다.

```
codex "로그인 기능이 있는 Flask 웹앱을 만들어줘"
```

### 과금 수준

Codex CLI는 OpenAI API를 직접 사용하므로 사용량에 따라 과금됩니다.

| 모델 | 입력 토큰 단가 | 비고 |
|---|---|---|
| gpt-4.1 | \$2 / 1M tokens | Codex CLI 기본 모델 |
| o4-mini | \$1.1 / 1M tokens | 추론 최적화, 코딩 권장 |

학습 목적의 소규모 프로젝트에서 하루 세션 기준 \$0.10\~\$0.50 수준입니다.

### 추가 선택지: VS Code + GitHub Copilot

VS Code 마켓플레이스에서 GitHub Copilot 확장을 설치합니다. GitHub 계정으로 로그인 후 활성화하면 됩니다. GitHub Student Developer Pack을 신청하면 Copilot을 무료로 이용할 수 있습니다.

```
https://education.github.com/pack
```

---

## 1.3 Lv.3 --- OpenAI API 직접 구성 (고급)

### 인터페이스

Python 코드로 OpenAI API를 직접 호출하는 방식입니다. Responses API, Agents SDK 등을 활용해 복잡한 파이프라인을 구성합니다.

### 설치 필요 소프트웨어

```
pip install openai streamlit python-dotenv requests
```

### 과금 수준

API 호출 단가에 사용량을 곱한 요금이 청구됩니다. `platform.openai.com/usage`에서 실시간으로 확인할 수 있습니다.

---

\newpage

# 2장. 작업 전 확정해야 할 사항

바이브 코딩에서 가장 많이 실패하는 이유는 "일단 해봐"로 시작하는 것입니다. AI에게 지시하기 전에 아래 사항을 반드시 확정하십시오. 이 과정 자체도 ChatGPT와 대화로 진행할 수 있습니다.

---

## 2.1 프로그래밍 언어 및 도구 스택 지정

AI는 지시하지 않으면 임의로 언어와 라이브러리를 선택합니다. 작업 시작 전 다음 항목을 명시적으로 선언하십시오.

### 확정 체크리스트

```
[ ] 프로그래밍 언어: Python 3.11 / JavaScript / TypeScript 등
[ ] 실행 환경: 로컬 PC / 웹 브라우저 / 서버
[ ] UI 프레임워크: Streamlit / Flask / React / 없음
[ ] 데이터 저장: 파일(JSON, CSV) / SQLite / 없음
[ ] 외부 API 사용 여부: OpenAI API / 날씨 API / 없음
[ ] Python 패키지 관리: pip + venv / conda
[ ] 운영체제: Windows / macOS / Linux
```

### 스택 선언 프롬프트 예시

> "지금부터 내가 요청하는 모든 코드는 다음 조건을 반드시 지켜줘.
> 언어: Python 3.11, UI: Streamlit, API: OpenAI GPT-4o-mini, 패키지 관리: pip + venv, OS: Windows 11.
> 외부 라이브러리 사용 시 pip install 명령을 반드시 함께 알려줘. 코드에 한국어 주석을 달아줘."

이 선언문을 대화 첫 번째 메시지로 전송하면, 이후 모든 코드가 해당 조건에 맞게 생성됩니다.

---

## 2.2 과업의 목적과 구조 설계

코드를 요청하기 전에 "이 프로그램이 무엇을 해야 하는가"를 문서로 정리해 두어야 합니다. 이 문서를 기획 명세서(spec)라고 합니다.

### 기획 명세서에 포함할 항목

**1) 한 문장 목적 정의**

형식: "이 프로그램은 [사용자]가 [상황]에서 [행동]할 수 있도록 돕는다."

예시: "이 프로그램은 대학생이 논문 PDF를 업로드해 핵심 내용을 요약하고 Q&A를 할 수 있도록 돕는다."

**2) 사용자 흐름(User Flow) 정의**

사용자가 프로그램을 열었을 때부터 닫을 때까지의 단계를 번호로 나열합니다.

```
1. 사용자가 웹페이지를 연다
2. PDF 파일을 업로드한다
3. AI가 요약을 자동 생성해 화면에 표시한다
4. 사용자가 질문을 입력한다
5. AI가 PDF 내용을 바탕으로 답변한다
6. 대화를 저장하거나 종료한다
```

**3) 화면 구성(UI Layout) 묘사**

그림 없이 텍스트로 화면 배치를 설명합니다.

```
- 상단: 제목 텍스트 "논문 요약 AI"
- 왼쪽 사이드바: PDF 업로드 버튼, 업로드된 파일 목록
- 중앙: 요약 결과 표시 영역
- 하단: 질문 입력창 + 전송 버튼
```

**4) 데이터 흐름 정의**

```
입력: 사용자 업로드 PDF 파일
처리: PDF 텍스트 추출 → OpenAI API 전송 → 응답 수신
출력: 웹 화면에 요약 및 답변 표시
저장: 없음 (세션 종료 시 초기화)
```

**5) 하지 않을 것 명시 (Non-Goals)**

```
- 사용자 로그인 기능은 구현하지 않는다
- 데이터베이스는 사용하지 않는다
- 모바일 최적화는 고려하지 않는다
```

---

## 2.3 ChatGPT로 기획 명세서 작성하기

기획 아이디어만 있다면 ChatGPT가 명세서 작성을 도와줄 수 있습니다.

### 프롬프트 예시

> "내가 만들고 싶은 프로그램은 [아이디어 설명]이야. 이 프로그램의 기획 명세서를 작성해줘. 목적 정의, 사용자 흐름, UI 구성, 데이터 흐름, Non-Goals를 포함해줘. 내가 미처 생각하지 못한 부분이 있으면 질문해서 확정한 다음 명세서를 완성해줘."

---

\newpage

# 3장. 구사 가능한 작업의 범위, 수준, 한계

## 3.1 레벨별 작업 가능 범위

### Lv.1 --- ChatGPT 웹 (입문)

**가능한 작업**

단일 파일(.py, .html, .js) 생성 및 수정, 50\~300줄 이하의 독립 실행 스크립트, 간단한 Streamlit 웹앱, 데이터 분석 및 시각화 코드, 엑셀/CSV 처리 자동화, 텍스트 처리/번역/요약 스크립트, 간단한 API 호출 코드를 다룰 수 있습니다.

**한계**

파일 간 의존 관계가 복잡한 다중 파일 프로젝트는 일관성 유지가 어렵습니다. 500줄 이상 코드는 컨텍스트 초과로 품질이 저하될 수 있습니다. 이전 대화를 기억하지 못하므로 긴 세션에서 누락이 발생합니다. 실행 환경(사용자 PC)에 직접 접근이 불가합니다.

---

### Lv.2 --- Codex CLI / VS Code Copilot (중급)

**가능한 작업**

다중 파일 프로젝트 동시 편집, 기존 코드베이스를 읽고 맥락에 맞게 수정, 테스트 코드 자동 생성, 리팩토링 및 코드 최적화, Git과 연계한 커밋 메시지 생성, Flask/FastAPI 백엔드 구축, 데이터베이스 스키마 생성 및 쿼리 작성이 가능합니다.

**한계**

복잡한 알고리즘 설계는 여전히 사람의 검토가 필요합니다. 보안 취약점을 자동으로 발견하지 못합니다. 대규모 코드베이스(수만 줄)에서 전체 맥락 파악에 한계가 있습니다.

---

### Lv.3 --- API 직접 활용 (고급)

**가능한 작업**

멀티 에이전트 시스템 구성, 자동화 파이프라인(데이터 수집 → 처리 → 결과 출력), RAG(검색 증강 생성) 구조 구현, 반복 작업 자동화(배치 처리), 평가 루프(Evaluation Loop) 구성, 다른 서비스(이메일, 슬랙, 구글 시트 등)와 연동이 가능합니다.

**한계**

과금이 발생하므로 비용 관리가 필요합니다. API 응답 오류 처리 코드를 직접 작성해야 합니다. 프로덕션 수준 보안과 인증은 별도 설계가 필요합니다.

---

## 3.2 바이브 코딩의 구조적 한계 (공통)

바이브 코딩은 강력하지만 아래 한계를 명확히 인식해야 합니다.

| 한계 | 설명 |
|---|---|
| 검증 책임 | AI가 생성한 코드가 올바른지 확인하는 것은 사람의 몫 |
| 저작권 불확실성 | 생성된 코드의 라이선스 출처가 불명확할 수 있음 |
| 보안 취약점 | AI는 보안을 자동 보장하지 않음. 입력값 검증 필수 |
| 비결정성 | 같은 프롬프트라도 결과가 매번 다를 수 있음 |
| 환각(Hallucination) | 존재하지 않는 라이브러리나 함수를 생성하는 경우 있음 |
| 컨텍스트 손실 | 대화가 길어질수록 초기 조건을 망각하는 경향 |

---

\newpage

# 4장. 작업 절차 안내

## 4.1 전체 워크플로 개요

```
[단계 1] 기획 명세서 작성
      |
      v
[단계 2] 스택 선언 프롬프트 전송
      |
      v
[단계 3] 초기 코드 생성 요청
      |
      v
[단계 4] 로컬 실행 및 테스트
      |
      +--[오류 발생]--> [단계 5A] 디버깅 요청
      |
      +--[기능 추가]--> [단계 5B] 수정 요청
      |
      v
[단계 6] 반복 (단계 4~5)
      |
      v
[단계 7] 최종 정리 및 배포/제출
```

---

## 4.2 단계별 프롬프트 예시

### 단계 2: 스택 선언 + 과업 설명 (첫 번째 메시지)

> "지금부터 바이브 코딩 세션을 시작할게. 먼저 규칙부터 정하자.
>
> 고정 조건 (절대 변경하지 말 것): 언어는 Python 3.11, UI는 Streamlit, API는 OpenAI GPT-4o-mini, 패키지 관리는 pip + venv, OS는 Windows 11, 코드 주석은 한국어로, 라이브러리 추가 시 pip install 명령 반드시 포함.
>
> 만들 것: 사용자가 뉴스 URL을 붙여넣으면 AI가 핵심 내용을 요약하고 3줄 briefing을 생성해주는 Streamlit 웹앱.
>
> 먼저 이 기획에서 내가 놓친 것이 있는지 질문해줘. 확정 후 코드를 만들자."

---

### 단계 3: 초기 코드 생성 요청

> "확인 완료. 이제 전체 코드를 작성해줘. 단, 다음 순서로 해줘. 1) 먼저 파일 구조를 보여줘. 2) 각 파일의 코드를 순서대로 보여줘. 3) 실행 방법을 단계별로 알려줘."

---

### 단계 4: 기능 추가 요청

> "지금 코드에서 다음 기능을 추가해줘. 기존 코드 전체를 다시 보여주되, 변경된 부분은 주석으로 `# [추가됨]` 또는 `# [수정됨]` 표시를 달아줘. 추가 기능: 요약 결과를 복사 버튼 한 번으로 클립보드에 복사할 수 있어야 함."

---

### 단계 5: 디버깅 요청

> "아래 오류가 발생했어. 오류 메시지 전체를 붙여넣을게. 어느 줄에서 왜 발생하는지 설명하고, 수정된 코드를 보여줘. 수정 시 다른 부분은 건드리지 말고 오류가 발생한 부분만 최소한으로 수정해줘.
>
> [오류 메시지 전체 복사 붙여넣기]"

---

### 단계 6: 코드 검토 요청

> "지금 완성된 코드를 보안, 성능, 가독성 관점에서 검토해줘. 문제가 있으면 무엇이 문제인지, 왜 문제인지, 어떻게 고쳐야 하는지를 각각 설명해줘. 수정이 필요한 부분만 수정된 코드 조각으로 보여줘."

---

## 4.3 명세 문서(.md 파일) 구성 및 작성 원칙

복잡한 프로젝트를 진행할 때는 ChatGPT 대화창에 **명세 .md 파일을 첨부**하는 것이 핵심입니다. 이 파일이 있으면 새 대화를 시작해도 AI가 맥락을 유지할 수 있습니다.

### 명세 파일(spec.md)의 기본 구성 예시

```markdown
# 프로젝트 명세서

## 1. 프로젝트 개요
- 이름: 뉴스 요약 AI
- 목적: 사용자가 URL을 입력하면 뉴스 핵심을 3줄로 요약
- 최종 형태: Streamlit 웹앱, 로컬 실행

## 2. 기술 스택 (절대 변경 금지)
- 언어: Python 3.11
- UI: Streamlit 1.x
- AI: OpenAI API, 모델 gpt-4o-mini
- 기타: requests, python-dotenv
- 실행환경: Windows 11, venv

## 3. 파일 구조
my_project/
  app.py          # Streamlit 메인 앱
  summarizer.py   # 요약 로직
  .env            # API 키 (제출 제외)
  requirements.txt

## 4. 사용자 흐름
1. 앱 실행 후 웹페이지 표시
2. URL 입력창에 뉴스 URL 붙여넣기
3. [요약] 버튼 클릭
4. 3줄 요약 결과 표시
5. [복사] 버튼으로 클립보드 저장

## 5. 각 파일의 역할과 주요 함수
### app.py
- Streamlit UI 구성 및 사용자 입력 수신
- summarizer.py 호출

### summarizer.py
- fetch_url(url): URL에서 텍스트 추출
- summarize(text): OpenAI API 호출해 요약 생성
- 반환값: 요약 문자열 (3줄)

## 6. 완료된 기능 체크리스트
- [x] URL 입력 및 텍스트 추출
- [x] OpenAI API 요약 호출
- [ ] 복사 버튼
- [ ] 에러 처리 (잘못된 URL)

## 7. 변경 이력
- 2026-04-10: 초기 버전 완성
- 2026-04-11: 복사 버튼 추가 예정

## 8. 하지 않을 것 (Non-Goals)
- 로그인/회원가입 기능 없음
- DB 저장 없음
- 모바일 UI 최적화 없음
```

### 명세 파일 작성 원칙

구체적 수치를 명시합니다. "빠르게"가 아닌 "응답 시간 3초 이하"처럼 씁니다. 금지 사항을 명시합니다. "변경 금지" 항목을 명확히 표기합니다. 완료 상태를 체크리스트로 추적합니다. 변경 이력을 날짜별로 기록합니다. 새 대화 시작 시 항상 첨부하며 "이 명세서 기반으로 작업 이어서 하자"고 시작합니다.

---

## 4.4 디버깅, 수정, 검증 절차

### 오류 유형별 대응 방법

**유형 1. 실행 오류 (빨간색 오류 메시지)**

오류 메시지 전체를 터미널에서 복사합니다. ChatGPT에 "아래 오류 발생. 원인과 수정 방법을 알려줘"와 함께 붙여넣습니다. 수정된 코드의 해당 줄만 적용합니다. 전체 교체는 다른 부분을 망가뜨릴 수 있습니다.

**유형 2. 논리 오류 (실행은 되지만 결과가 이상함)**

어떤 입력에 어떤 결과가 나왔는지를 구체적으로 설명합니다. 기대한 결과가 무엇인지 함께 명시합니다. 예시: "URL을 입력했을 때 요약이 아닌 빈 화면이 나와. 기대값은 3줄 요약 텍스트, 실제값은 빈 화면."

**유형 3. 라이브러리 설치 오류**

가상환경이 활성화되어 있는지 확인합니다. `(.venv)` 표시가 있어야 합니다. pip install 명령 앞에 `python -m`을 추가해서 재시도합니다. 그래도 안 되면 오류 메시지를 그대로 ChatGPT에 붙여넣습니다.

### 검증 체크리스트 (제출 전 확인)

```
[ ] 모든 기능이 정상 작동하는가
[ ] 존재하지 않는 라이브러리를 import하고 있지는 않은가
[ ] API 키가 .py 코드 안에 직접 쓰여 있지 않은가
[ ] 예상치 못한 입력(빈 값, 긴 텍스트)에도 crash하지 않는가
[ ] requirements.txt로 환경 재현이 가능한가
```

### requirements.txt 생성 방법

프로젝트 완성 후 아래 명령으로 사용한 라이브러리 목록을 저장합니다.

```
pip freeze > requirements.txt
```

다른 컴퓨터에서 동일 환경을 재현할 때는 아래 명령을 사용합니다.

```
pip install -r requirements.txt
```

---

## 4.5 최종 사용 및 배포 시 유의사항

### 개인 사용 (로컬)

`.env` 파일에는 API 키가 들어 있으므로, 다른 사람과 파일을 공유할 때 `.env`는 반드시 제외합니다. ZIP 파일로 압축해 제출할 때도 `.env` 제외 후 압축합니다.

### 온라인 배포 (Streamlit Cloud 등)

Streamlit Cloud를 이용하면 무료로 웹에 앱을 배포할 수 있습니다.

절차 요약: GitHub 저장소에 `app.py`와 `requirements.txt`를 업로드합니다(`.env`는 절대 포함 금지). `https://streamlit.io/cloud`에서 GitHub 연동 후 앱을 배포합니다. Streamlit Cloud의 Secrets 설정 메뉴에 API 키를 입력합니다.

배포 전 `.gitignore` 파일을 프로젝트 폴더에 만들고 아래 내용을 저장합니다.

```
.env
.venv/
__pycache__/
*.pyc
```

### 저작권 및 학술 윤리

AI가 생성한 코드를 과제로 제출할 때는 담당 교수의 AI 사용 정책을 반드시 확인합니다. AI 도움을 받았다면 어느 부분에 어떻게 활용했는지 명시하는 것을 권장합니다. 생성된 코드에 포함된 외부 라이브러리는 각각의 오픈소스 라이선스를 따릅니다.

---

\newpage

# 5장. 고급 단계 --- Harness Engineering

## 5.1 Harness Engineering이란?

바이브 코딩이 숙련될수록 단순히 "코드를 만들어 달라"는 요청만으로는 한계에 부딪힙니다. **Harness Engineering**은 AI가 생성한 코드를 자동으로 실행하고 테스트하고 평가하는 **검증 인프라(harness)를 먼저 설계하는 방법론**입니다.

전통적 개발에서 테스트 주도 개발(TDD)에 해당하는 개념이며, 바이브 코딩에서는 다음과 같이 재해석됩니다.

> "AI에게 기능 코드를 만들기 전에, 그 코드가 올바른지 판정하는 평가 도구를 먼저 만들게 한다."

---

## 5.2 Harness Engineering이 필요한 시점

아래 상황 중 하나라도 해당하면 harness 설계를 먼저 해야 합니다.

- 생성된 코드의 품질을 사람이 일일이 확인하기 어려울 때
- 동일한 기능을 여러 방식으로 구현하고 비교하고 싶을 때
- 코드 수정 후 기존 기능이 깨지는지 자동으로 확인하고 싶을 때
- 대량의 입력 데이터에 대해 결과를 자동 검사하고 싶을 때
- AI 에이전트가 반복적으로 작업을 수행하는 파이프라인을 구축할 때

---

## 5.3 Harness Engineering의 기본 구조

```
[입력 데이터셋]
      |
      v
[실행할 코드 / 에이전트]
      |
      v
[출력 결과]
      |
      v
[평가 함수 (Evaluator)]
      |
      v
[평가 결과 리포트]
      |
      v
[통과/실패 기준 --> 재시도 또는 확정]
```

---

## 5.4 단계별 절차

### 단계 1: 평가 기준(Rubric) 먼저 정의

코드를 만들기 전에 "올바른 결과란 무엇인가"를 수치와 규칙으로 정의합니다.

뉴스 요약 AI의 평가 기준 예시:

| 기준 | 가중치 | 판정 방법 |
|---|---|---|
| 핵심 키워드 포함 | 40% | 원문의 주요 명사 3개 이상 포함 여부 |
| 길이 준수 | 20% | 3줄 이하, 각 줄 50자 이하 |
| 언어 일치 | 20% | 원문이 한국어면 요약도 한국어 |
| 사실 왜곡 없음 | 20% | 원문에 없는 내용 추가 여부 (수동 검토) |

### 단계 2: 테스트 입력 데이터셋 준비

평가에 사용할 입력 예시를 최소 5\~10개 준비합니다.

```python
# test_cases.py
TEST_INPUTS = [
    {
        "id": "TC001",
        "url": "https://example.com/news1",
        "expected_keywords": ["반도체", "수출", "증가"],
        "expected_lines": 3,
    },
    {
        "id": "TC002",
        "url": "https://example.com/news2",
        "expected_keywords": ["AI", "투자", "스타트업"],
        "expected_lines": 3,
    },
]
```

### 단계 3: Evaluator 함수 작성 요청

ChatGPT에게 평가 함수를 먼저 만들어달라고 요청합니다.

> "아래 rubric을 기반으로 요약 결과를 자동 평가하는 `evaluate_summary(original_text, summary, expected_keywords)` 함수를 작성해줘. 함수는 각 기준별 점수(0\~1)와 총점, 실패 이유 목록을 딕셔너리로 반환해야 해. [rubric 내용 붙여넣기]"

### 단계 4: Harness 실행 스크립트 작성 요청

> "위의 evaluator 함수와 test_cases.py를 사용해서, 모든 테스트 케이스를 자동으로 실행하고 결과를 표 형식으로 출력하는 `run_harness.py`를 작성해줘. 각 테스트 케이스의 통과/실패 여부와 점수를 보여주고, 마지막에 전체 평균 점수도 출력해줘."

### 단계 5: 기능 코드와 Harness를 함께 실행

```
python run_harness.py
```

출력 예시:

```
테스트 결과 요약
================
TC001: PASS  (총점: 0.87)
TC002: FAIL  (총점: 0.52, 실패 이유: 키워드 누락)
TC003: PASS  (총점: 0.91)

전체 평균: 0.77 / 1.00
통과율: 66.7% (3개 중 2개 통과)
```

### 단계 6: 실패 케이스 기반 프롬프트 개선

> "TC002가 실패했어. 실패 이유는 '키워드 누락'이야. 원문과 기대 키워드, 현재 요약 결과를 아래에 붙여넣을게. 어떤 부분을 수정하면 TC002도 통과할 수 있을지 분석해줘. 단, 수정이 TC001과 TC003의 점수를 낮추지 않도록 해줘."

---

## 5.5 Harness Engineering 심화: LLM-as-Judge 패턴

평가 기준이 수치로 정의하기 어려운 경우(문체, 창의성, 자연스러움 등), GPT 모델 자체를 평가자(judge)로 활용합니다.

Evaluator 프롬프트 설계 예시:

```python
JUDGE_PROMPT = """
당신은 텍스트 품질을 평가하는 전문가입니다.
아래의 원문과 요약을 읽고 다음 기준으로 점수를 매겨주세요.

[원문]
{original}

[요약]
{summary}

평가 기준:
1. 정확성 (1~5점): 원문 내용을 왜곡 없이 전달하는가
2. 간결성 (1~5점): 불필요한 내용 없이 핵심만 담았는가
3. 가독성 (1~5점): 자연스럽고 읽기 쉬운가

반드시 다음 JSON 형식으로만 응답하세요:
{"accuracy": 점수, "brevity": 점수, "readability": 점수, "reason": "이유"}
"""
```

---

## 5.6 프로젝트 규모별 Harness 권장 구성

| 규모 | 권장 harness 구성 |
|---|---|
| 소형 (1\~2일) | 수동 테스트 5개 + 간단한 assert 검사 |
| 중형 (1주) | 자동화된 evaluator + 10\~20개 테스트 케이스 |
| 대형 (2주 이상) | LLM-as-Judge + 배치 실행 + 결과 CSV 저장 + 반복 개선 루프 |

---

## 5.7 Harness Engineering 요약 워크플로

```
1. Rubric 정의 (무엇이 "좋은 결과"인가)
         |
         v
2. 테스트 데이터셋 준비 (최소 5개 케이스)
         |
         v
3. Evaluator 코드 작성 (ChatGPT에 요청)
         |
         v
4. 기능 코드 작성 (기존 방식대로)
         |
         v
5. run_harness.py 실행 --> 결과 확인
         |
         v
6. 실패 케이스 분석 --> 프롬프트/코드 수정
         |
         v
7. 재실행 --> 목표 통과율 달성 시 완료
```

---

\newpage

# 부록 A. 플랫폼별 빠른 참조표

| 항목 | ChatGPT Plus | Codex CLI | API 직접 |
|---|---|---|---|
| 월 요금 | \$20 고정 | 사용량 기반 | 사용량 기반 |
| 설치 필요 | 없음 | Node.js + npm | Python + pip |
| 파일 편집 | 수동 복붙 | 자동 | 자동 |
| 다중 파일 | 제한적 | 가능 | 가능 |
| 초보자 접근성 | 매우 쉬움 | 보통 | 어려움 |
| 권장 프로젝트 규모 | 소형 | 중형 | 대형 |

---

# 부록 B. 유용한 리소스

- OpenAI 플랫폼: `https://platform.openai.com`
- Codex CLI 공식 저장소: `https://github.com/openai/codex`
- Streamlit 공식 문서: `https://docs.streamlit.io`
- GitHub Student Developer Pack: `https://education.github.com/pack`
- Streamlit Cloud 배포: `https://streamlit.io/cloud`
- OpenAI 사용량 모니터링: `https://platform.openai.com/usage`

# =====Anthropic 바이브 코딩 플랫폼에 대한 Claude의 설명=====
---
title: "Anthropic Claude로 시작하는 바이브 코딩 가이드"
subtitle: "Claude.ai / Claude Code 기반 | 입문부터 Harness Engineering까지"
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
  - \usepackage{xcolor}
  - \usepackage{listings}
  - \lstset{basicstyle=\ttfamily\small, breaklines=true, frame=single, backgroundcolor=\color{gray!10}}
  - \pagestyle{fancy}
  - \fancyhf{}
  - \fancyhead[L]{Anthropic Claude 바이브 코딩 가이드}
  - \fancyfoot[C]{\thepage}
---

\newpage

# 이 가이드를 읽기 전에

**바이브 코딩(Vibe Coding)** 이란, 프로그래밍 언어 문법을 몰라도 자연어로 AI에게 지시해 실제로 작동하는 코드를 만들어내는 작업 방식입니다. Andrej Karpathy가 2025년 초에 명명한 이 개념은 Anthropic의 **Claude Code**가 등장하면서 "진정한 바이브 코딩 머신"이라는 평가를 받으며 2026년 현재 가장 강력한 바이브 코딩 환경으로 자리 잡았습니다.

이 가이드는 **Anthropic의 서비스만**을 대상으로 합니다. 수강생의 기술 수준에 따라 세 가지 레벨로 구성되어 있습니다.

| 레벨 | 플랫폼 | 설치 필요 | 대상 |
|---|---|---|---|
| **Lv.1 입문** | Claude.ai 웹/앱 | 없음 | 코딩 경험 전무 |
| **Lv.2 중급** | Claude Code 데스크톱 + VS Code 확장 | 간단한 설치 | 터미널 미경험 가능 |
| **Lv.3 고급** | Claude Code CLI + CLAUDE.md 설계 | 터미널 사용 | 구조적 프로젝트 관리 |

---

\newpage

# 1장. Anthropic 바이브 코딩 플랫폼 개요

## 1.1 플랫폼 전체 지도

Anthropic은 2026년 현재 아래와 같은 바이브 코딩 관련 서비스를 제공합니다. 모두 같은 Claude 모델을 공유하지만 **인터페이스**, **파일 접근 권한**, **자율 실행 범위**가 다릅니다.

```
claude.ai (웹/모바일)
  |-- 채팅 + Artifacts 생성 (코드 미리보기·실행)
  |-- Projects (파일 공유, 커스텀 지시사항)
  `-- Cowork (데스크톱 앱: 파일·앱 자율 조작)

Claude Code
  |-- Desktop App (독립 실행형 GUI 에이전트)
  |-- VS Code / JetBrains 확장 (IDE 내부)
  `-- CLI (터미널 직접 실행, 최대 자율 권한)
```

---

## 1.2 플랜별 과금 및 기능 비교 (2026년 4월 기준)

| 플랜 | 월 요금 | Claude Code | 모델 | 용량 |
|---|---|---|---|---|
| **Free** | 무료 | 불가 | Sonnet 4.6 (제한) | 하루 소량 |
| **Pro** | \$20/월 | 포함 | Sonnet 4.6 + Opus 4.6 | Free의 5배 |
| **Max 5x** | \$100/월 | 포함 | 동일 + 우선 접근 | Pro의 5배 |
| **Max 20x** | \$200/월 | 포함 | 동일 + 최우선 | Pro의 20배 |

**학생 권장 플랜**: 처음 시작하는 학생은 **Free** 플랜으로 `claude.ai`에서 Lv.1을 경험한 뒤, 코딩 과제 제출을 위해 **Pro** 플랜(\$20/월)으로 업그레이드해 Claude Code를 사용하는 것을 권장합니다.

중요한 주의사항: **Claude Code는 Free 플랜에서 사용할 수 없습니다.** Pro 이상이 필요합니다.

또한 Claude.ai 구독(채팅 사용량)과 Claude Code 사용량은 **동일한 월간 사용량 풀을 공유**합니다. 채팅을 많이 하면 Claude Code 사용 가능 시간이 줄어듭니다.

---

## 1.3 각 플랫폼의 바이브 코딩 특성

### Claude.ai 웹 (Lv.1)

`claude.ai`의 채팅 인터페이스에서 코드를 요청하면 Artifacts 패널에 코드가 표시됩니다. HTML/JavaScript는 브라우저 내에서 즉시 실행 미리보기가 가능합니다. Python 등의 코드는 사용자가 복사해서 로컬에서 실행해야 합니다. **실제 파일에 대한 접근 권한은 없습니다.**

### Claude Code Desktop App (Lv.2)

터미널 없이 GUI로 Claude Code를 사용할 수 있는 독립 실행형 앱입니다. 로컬 파일을 직접 읽고 수정하며, VS Code와 연동해 시각적 diff(변경 내용 비교)를 제공합니다. macOS, Windows, Linux를 지원합니다.

### Claude Code CLI (Lv.3)

터미널에서 실행하는 전통적인 Claude Code입니다. 가장 강력한 자율 실행 권한을 가지며, 파일 편집, 명령 실행, Git 조작, 테스트 실행까지 자동으로 처리합니다. 2026년 현재 Anthropic 내부 코드의 대부분을 Claude Code가 작성하고 있습니다.

### Cowork (데스크톱 자동화)

Claude 데스크톱 앱에 포함된 기능으로, 클릭, 앱 실행, UI 조작 등 컴퓨터 화면을 직접 제어합니다. Pro 이상 플랜에서 사용 가능합니다.

---

\newpage

# 2장. 레벨별 접근 절차

## 2.1 Lv.1 --- Claude.ai 웹 인터페이스 (입문)

### 접속 및 시작

1. `https://claude.ai`에 접속합니다.
2. 구글 계정 또는 이메일로 회원가입합니다.
3. Free 플랜으로 바로 사용할 수 있습니다.

### 바이브 코딩에 유용한 기능: Projects

Projects는 파일과 커스텀 지시사항을 저장해 두면, 해당 프로젝트의 모든 대화에서 Claude가 그 컨텍스트를 유지하는 기능입니다.

활용 방법:

1. 왼쪽 사이드바에서 `New Project`를 클릭합니다.
2. 프로젝트 이름(예: "나의 Streamlit 앱")을 입력합니다.
3. `Project Instructions`에 아래와 같이 고정 지시사항을 작성합니다.

```
이 프로젝트의 모든 코드는 다음 조건을 따른다.
- 언어: Python 3.11
- UI: Streamlit
- OS: Windows 11
- 코드 주석: 한국어
- 라이브러리 추가 시 pip install 명령 반드시 포함
```

4. 이후 이 프로젝트 내의 모든 대화에 위 조건이 자동 적용됩니다.

### 설치 필요 소프트웨어

없음 (브라우저만 있으면 됨).

### 과금

Free 플랜으로 사용 가능. 단, 하루 사용 가능한 메시지 수에 제한이 있으며 피크 시간대(평일 낮)에는 속도가 느려질 수 있습니다.

---

## 2.2 Lv.2 --- Claude Code Desktop App (중급)

### 인터페이스

터미널 명령어 없이 GUI 창에서 Claude Code를 사용할 수 있습니다. 파일 구조를 시각적으로 확인하고, 변경 사항을 diff 형식으로 검토할 수 있습니다.

### 설치 절차

**사전 요구사항**: Pro 이상 플랜 보유, Windows 10 (v1809 이상) 또는 macOS 13 이상

**Windows 설치**

방법 1 (권장, 가장 간단): WinGet 사용

```
winget install Anthropic.ClaudeCode
```

방법 2: PowerShell 원라인 설치

```
iwr https://storage.googleapis.com/anthropic-claude-code/install.ps1 -UseBasicParsing | iex
```

설치 완료 후 터미널에서 아래 명령으로 버전을 확인합니다.

```
claude --version
```

**최초 인증**

```
claude
```

처음 실행하면 브라우저가 자동으로 열리고 Anthropic 계정 로그인 페이지가 표시됩니다. 로그인하면 인증 토큰이 자동으로 저장됩니다.

### VS Code 확장 설치 (선택, 강력 권장)

1. VS Code를 실행합니다.
2. 확장(Extensions) 패널에서 `Claude Code`를 검색합니다.
3. Anthropic이 게시한 확장을 설치합니다.
4. 설치 후 VS Code 내에서 인라인 diff, 코드 블록 선택 후 질의, 대화 이력 확인이 가능합니다.

### 과금

Pro 플랜(\$20/월) 이상 필요. Claude.ai 채팅 사용량과 동일한 풀을 사용합니다. 집중적인 코딩 세션 시 하루 중반에 사용량 한계에 도달할 수 있습니다.

---

## 2.3 Lv.3 --- Claude Code CLI (고급)

### 인터페이스

Windows Terminal 또는 명령 프롬프트에서 `claude` 명령으로 직접 실행합니다. 프로젝트 폴더 전체를 Claude가 읽고 수정하며, Git 커밋까지 자동으로 처리합니다.

### 설치

Lv.2의 설치 과정과 동일합니다. Desktop App과 CLI는 같은 바이너리에서 실행됩니다.

### 핵심 명령어

```
claude                    # 대화형 에이전트 시작
claude "태스크 설명"       # 단일 태스크 실행
claude --print "질문"     # 결과만 출력 (비대화형)
/init                    # CLAUDE.md 자동 생성
/help                    # 사용 가능한 명령어 목록
/settings                # 설정 보기 및 변경
/hooks                   # 자동화 훅 설정
```

---

\newpage

# 3장. 작업 전 확정해야 할 사항

## 3.1 스택 선언 --- 프로그래밍 언어 및 도구 지정

Claude는 지시하지 않으면 임의로 언어와 라이브러리를 선택합니다. 작업 시작 전 아래 항목을 명시적으로 선언해야 합니다.

### 확정 체크리스트

```
[ ] 프로그래밍 언어와 버전: Python 3.11 / JavaScript (Node.js 22) 등
[ ] 실행 환경: 로컬 PC / 웹 브라우저 / 서버(Linux VPS)
[ ] UI 프레임워크: Streamlit / Flask / React / Next.js / 없음
[ ] 데이터 저장: 파일(JSON, CSV) / SQLite / 없음
[ ] 외부 API: Anthropic Claude API / 날씨 API / 없음
[ ] 패키지 관리: pip + venv (Python) / npm (JavaScript)
[ ] 운영체제: Windows 11 / macOS / Linux
[ ] 버전 관리: Git 사용 여부
```

### 스택 선언 방법 (두 가지)

**방법 A: claude.ai Projects의 지시사항에 고정 작성 (Lv.1)**

Projects Instructions 입력창에 직접 씁니다.

**방법 B: CLAUDE.md 파일에 작성 (Lv.2 / Lv.3)**

프로젝트 폴더 루트에 `CLAUDE.md` 파일을 만들어 Claude Code가 항상 참조하게 합니다. 이 방법이 더 강력하고 지속적입니다. 자세한 내용은 3.3절을 참조하십시오.

---

## 3.2 과업의 목적과 구조 설계

코드를 요청하기 전에 "이 프로그램이 무엇을 해야 하는가"를 문서로 정리해야 합니다.

### 기획 명세서에 포함할 5가지 항목

**1) 한 문장 목적 정의**

형식: "이 프로그램은 [사용자]가 [상황]에서 [행동]할 수 있도록 돕는다."

예시: "이 프로그램은 대학생이 논문 PDF를 업로드해 핵심 내용을 요약하고 Q&A를 할 수 있도록 돕는다."

**2) 사용자 흐름(User Flow)**

```
1. 사용자가 웹페이지를 연다
2. PDF 파일을 업로드한다
3. AI가 요약을 자동 생성해 화면에 표시한다
4. 사용자가 질문을 입력한다
5. AI가 PDF 내용을 바탕으로 답변한다
```

**3) 화면 구성(UI Layout) 텍스트 묘사**

```
- 상단: 제목 "논문 요약 AI"
- 왼쪽 사이드바: PDF 업로드 버튼, 파일 목록
- 중앙: 요약 결과 표시 영역
- 하단: 질문 입력창 + 전송 버튼
```

**4) 데이터 흐름**

```
입력: 사용자 업로드 PDF
처리: 텍스트 추출 → Claude API 전송 → 응답 수신
출력: 웹 화면에 요약 및 답변 표시
저장: 없음 (세션 종료 시 초기화)
```

**5) 하지 않을 것(Non-Goals)**

```
- 사용자 로그인 기능 없음
- 데이터베이스 사용 안 함
- 모바일 최적화 없음
```

---

## 3.3 CLAUDE.md --- Claude Code의 핵심 설정 파일

`CLAUDE.md`는 Claude Code 프로젝트 루트에 두는 마크다운 파일로, Claude가 **매 턴마다 다시 읽는 영구 컨텍스트**입니다. 이 파일 하나가 세션이 길어지거나 새 세션을 시작해도 일관성을 유지하는 핵심입니다.

### CLAUDE.md 자동 생성 방법

Claude Code를 프로젝트 폴더에서 실행한 뒤 아래 명령을 입력합니다.

```
/init
```

Claude Code가 기존 코드를 분석해 빌드 명령, 테스트 방법, 코드 패턴을 자동으로 감지해 `CLAUDE.md`를 생성합니다.

### 학생용 CLAUDE.md 기본 템플릿

아래 내용을 참고해 프로젝트에 맞게 작성합니다. **50\~100줄 이내로 간결하게** 유지하십시오. 각 줄마다 "이게 없으면 Claude가 실수할까?"를 자문하고, 그렇지 않으면 삭제합니다.

```markdown
# CLAUDE.md

## 프로젝트 개요
- 이름: 논문 요약 AI
- 목적: 사용자가 PDF를 업로드해 요약 및 Q&A를 수행
- 최종 형태: Streamlit 웹앱, 로컬 실행

## 기술 스택 (절대 변경 금지)
- 언어: Python 3.11
- UI: Streamlit
- AI: Anthropic Claude API (claude-sonnet-4-6 모델)
- 기타: anthropic, python-dotenv, pymupdf
- 실행환경: Windows 11, pip + venv
- 코드 주석: 한국어

## 실행 명령
- 앱 시작: `streamlit run app.py`
- 의존성 설치: `pip install -r requirements.txt`
- 가상환경 활성화: `.venv\Scripts\activate`

## 파일 구조
my_project/
  app.py              # Streamlit 메인 앱
  summarizer.py       # 요약 로직 (Claude API 호출)
  .env                # API 키 (절대 커밋 금지)
  requirements.txt    # 의존성 목록
  CLAUDE.md           # 이 파일
  docs/               # 테스트용 PDF 파일 보관 폴더

## 주요 함수 및 모듈
- summarizer.extract_text(pdf_path): PDF에서 텍스트 추출
- summarizer.summarize(text): Claude API로 요약 생성
- summarizer.answer(text, question): Q&A 처리

## 환경변수 (.env)
ANTHROPIC_API_KEY=sk-ant-...

## 작업 완료 체크리스트
- [x] PDF 업로드 및 텍스트 추출
- [x] Claude API 요약 호출
- [ ] Q&A 기능
- [ ] 오류 처리 (잘못된 파일 형식)

## 변경 금지 사항
- requirements.txt의 anthropic 버전은 0.40.0 이상 유지
- API 키를 .py 코드 안에 직접 쓰지 않음
- 데이터베이스는 사용하지 않음
```

---

\newpage

# 4장. 구사 가능한 작업의 범위, 수준, 한계

## 4.1 레벨별 작업 가능 범위

### Lv.1 --- Claude.ai 웹 (입문)

**가능한 작업**

단일 파일 코드 생성 및 수정, 100줄 이하의 독립 실행 스크립트, HTML/JavaScript 즉시 미리보기(Artifacts), 데이터 분석 코드, 텍스트 처리/번역/요약 스크립트, 간단한 API 호출 코드.

**한계**

파일에 직접 접근 불가(복사·붙여넣기만 가능). 500줄 이상 코드는 컨텍스트 초과로 품질 저하 가능. 코드 실행 결과를 Claude가 직접 확인하지 못함. 장시간 세션에서 초기 조건 망각 가능.

---

### Lv.2 --- Claude Code Desktop App + VS Code (중급)

**가능한 작업**

다중 파일 프로젝트 동시 편집. 기존 코드베이스를 읽고 맥락에 맞게 수정. 테스트 코드 자동 생성 및 실행. 리팩토링 및 코드 최적화. Git 커밋 메시지 자동 생성. Streamlit / Flask 앱 전체 구조 생성. VS Code 내 인라인 수정 요청.

**한계**

복잡한 알고리즘 설계는 사람의 검토 필요. 보안 취약점을 자동으로 발견하지 못함.

---

### Lv.3 --- Claude Code CLI (고급)

**가능한 작업**

멀티 에이전트 팀(복수의 Claude 인스턴스 병렬 실행). CI/CD 파이프라인 자동화. 전체 리포지터리 수준의 리팩토링(수만 줄). 테스트 실패 자동 감지 후 코드 수정 반복 실행. GitHub Actions와 연동해 풀 리퀘스트 자동 생성. `/schedule` 명령으로 예약 작업 등록.

**한계**

과금 소비가 빠름. 세션이 길어지면 context compaction(맥락 압축)이 발생해 초기 지시사항 일부 손실 가능. CLAUDE.md로 보완 필요.

---

## 4.2 Anthropic Claude 바이브 코딩의 공통 한계

| 한계 | 설명 | 완화 방법 |
|---|---|---|
| 검증 책임 | 생성 코드가 올바른지 확인은 사람의 몫 | 테스트 코드 자동 생성 요청 |
| 환각(Hallucination) | 존재하지 않는 함수나 라이브러리 생성 가능 | `pip install` 전 라이브러리 실존 확인 |
| 컨텍스트 손실 | 긴 세션에서 초기 조건 망각 | CLAUDE.md에 핵심 조건 기록 |
| 보안 미보장 | API 키 노출, 입력값 검증 누락 가능 | .env 파일, 코드 보안 검토 요청 |
| 사용량 공유 | 채팅과 코딩이 같은 사용량 풀 사용 | 복잡한 채팅을 Projects로 분리 |
| 비결정성 | 같은 프롬프트라도 결과가 다를 수 있음 | 재현성이 필요하면 온도(temperature) 0 지정 요청 |

---

\newpage

# 5장. 작업 절차 안내

## 5.1 전체 워크플로 개요

```
[단계 1] 기획 명세서 작성 (claude.ai 대화로 작성 가능)
      |
      v
[단계 2] CLAUDE.md 또는 Projects 지시사항 작성
      |
      v
[단계 3] 초기 코드 생성 요청
      |
      v
[단계 4] 로컬 실행 및 결과 확인
      |
      +--[오류 발생]--> [단계 5A] 디버깅 요청
      |
      +--[기능 추가]--> [단계 5B] 기능 확장 요청
      |
      v
[단계 6] 반복 (단계 4~5)
      |
      v
[단계 7] 코드 검토 및 정리
      |
      v
[단계 8] 최종 제출 / 배포
```

---

## 5.2 단계별 프롬프트 예시

### 단계 2: 스택 선언 (claude.ai 대화 또는 Projects 지시사항)

> "지금부터 바이브 코딩 세션을 시작한다. 아래 조건을 모든 코드에 반드시 적용해라.
>
> 고정 조건 (절대 변경 금지): Python 3.11, UI는 Streamlit, AI는 Anthropic Claude API (claude-sonnet-4-6), 패키지 관리는 pip + venv, OS는 Windows 11, 코드 주석은 한국어, 라이브러리 추가 시 pip install 명령 반드시 포함.
>
> 이 조건에 대해 이해했으면 '조건 확인 완료'라고 답하고 내 다음 지시를 기다려라."

---

### 단계 3: 초기 코드 생성 요청

> "이제 전체 코드를 생성해라. 다음 순서로 진행해라. 첫째, 필요한 파일 목록과 각 파일의 역할을 먼저 보여줘라. 둘째, 파일을 순서대로 전체 코드와 함께 보여줘라. 셋째, 실행 방법을 단계별로 안내해라."

---

### 단계 4: 기능 추가 요청

> "현재 코드에 다음 기능을 추가해라. 변경된 줄에는 `# [추가됨]` 또는 `# [수정됨]` 주석을 달아라. 기존 기능은 변경하지 마라.
>
> 추가 기능: 요약 결과 아래에 '이 요약 복사하기' 버튼을 추가하고, 버튼 클릭 시 클립보드에 저장한다."

---

### 단계 5: 디버깅 요청

> "아래 오류가 발생했다. 오류 메시지 전체를 그대로 붙여넣겠다. 어느 줄에서 왜 발생하는지 설명하고, 수정된 코드 조각만 보여줘라. 다른 부분은 변경하지 마라.
>
> [오류 메시지 전체 붙여넣기]"

---

### Claude Code CLI에서의 직접 지시 예시

```
claude "PDF를 업로드하면 요약해주는 Streamlit 앱을 만들어줘.
        Python 3.11, Anthropic API, 코드 주석은 한국어로."
```

또는 대화형으로 실행한 후 프롬프트에 입력합니다.

---

### 코드 검토 요청 (단계 7)

> "완성된 코드를 다음 세 가지 관점에서 검토해라. 첫째 보안(API 키 노출, 입력값 검증 누락), 둘째 오류 처리(예외 상황에서 앱이 죽지 않는지), 셋째 가독성(주석이 충분한지). 문제가 있으면 무엇이 왜 문제인지, 어떻게 고쳐야 하는지를 설명하고 수정된 부분만 코드로 보여줘라."

---

## 5.3 .md 파일 종류별 구성 및 작성 원칙

Claude Code 프로젝트에서는 역할이 다른 여러 `.md` 파일을 사용합니다. 각 파일의 목적을 명확히 구분하면 Claude가 일관된 작업을 수행합니다.

### 파일 종류 개요

| 파일명 | 위치 | 역할 | Claude가 읽는 시점 |
|---|---|---|---|
| `CLAUDE.md` | 프로젝트 루트 | 기술 스택, 금지 사항, 실행 명령 | 매 턴 자동 |
| `spec.md` | 프로젝트 루트 | 기획 명세서, 사용자 흐름, UI 설계 | 필요 시 참조 요청 |
| `progress.md` | 프로젝트 루트 | 완료/미완료 기능 체크리스트 | 세션 재개 시 참조 |
| `.claude/commands/*.md` | 숨김 폴더 | 반복 사용 커스텀 명령어 정의 | /명령어 호출 시 |
| `HARNESS.md` | 프로젝트 루트 | 평가 기준(Rubric), 테스트 규칙 | Lv.3 Harness용 |

---

### spec.md (기획 명세서) 예시

```markdown
# 기획 명세서 (spec.md)

## 1. 프로젝트 목적
대학생이 논문 PDF를 업로드해 핵심 내용을 요약하고 Q&A를 수행하는 Streamlit 웹앱.

## 2. 사용자 흐름
1. 앱 실행 후 웹페이지 표시
2. 사이드바에서 PDF 파일 업로드
3. [요약 생성] 버튼 클릭 -> 중앙 패널에 3문단 요약 표시
4. 하단 입력창에 질문 입력 -> Claude API 호출 -> 답변 표시
5. [대화 초기화] 버튼으로 새 논문 분석 시작

## 3. 화면 구성
- 상단: 제목 + 현재 분석 중인 파일명 표시
- 왼쪽 사이드바: PDF 업로드 버튼, 파일 정보
- 중앙 상단: 요약 결과 (접기/펼치기 가능)
- 중앙 하단: 대화 히스토리 (멀티턴)
- 하단 고정: 질문 입력창

## 4. 데이터 흐름
입력: PDF 파일 (최대 20MB)
처리: PyMuPDF로 텍스트 추출 -> Anthropic API 전송
출력: 요약 텍스트 + Q&A 답변
저장: 없음 (세션 종료 시 초기화)

## 5. Non-Goals
- 로그인/회원가입 없음
- 데이터베이스 사용 안 함
- 영어 이외 언어 PDF에서 오류 허용
```

---

### progress.md (작업 진행 상황) 예시

```markdown
# 작업 진행 상황 (progress.md)

## 완료된 기능
- [x] PDF 업로드 UI 구성
- [x] PyMuPDF로 텍스트 추출
- [x] Claude API 연동 (claude-sonnet-4-6)
- [x] 요약 기능 (3문단)
- [x] 멀티턴 Q&A

## 진행 중
- [ ] 요약 결과 복사 버튼 (오늘 작업 예정)
- [ ] 오류 처리: 텍스트가 없는 스캔 PDF 대응

## 알려진 버그
- 100페이지 이상 PDF에서 토큰 초과 오류 발생
  - 임시 해결: 앞 50페이지만 추출하도록 제한

## 변경 이력
- 2026-04-10: 초기 버전 완성
- 2026-04-11: 멀티턴 Q&A 추가
- 2026-04-12: 토큰 초과 오류 임시 수정
```

---

### .claude/commands/review.md (커스텀 슬래시 명령어) 예시

이 파일을 만들면 Claude Code 세션에서 `/review` 명령으로 호출할 수 있습니다.

```markdown
현재 git diff를 다음 기준으로 검토해라:

1. 보안 취약점 (API 키 노출, SQL 인젝션 가능성)
2. 오류 처리 누락 (try-except 없는 외부 호출)
3. CLAUDE.md의 코딩 컨벤션 위반
4. 성능 문제 (루프 내 API 호출 등)

$ARGUMENTS가 있으면 그 모듈에 집중해서 검토하고,
없으면 전체 diff를 대상으로 한다.
결과는 심각도 순서로 나열해라 (Critical > High > Medium > Low).
```

---

## 5.4 디버깅, 수정, 검증 절차

### 오류 유형별 대응

**유형 1. 실행 오류 (터미널 빨간색 오류)**

오류 메시지 전체를 복사해 Claude에게 전달합니다. "어느 줄에서 왜 발생하는지 설명하고, 해당 부분만 최소한으로 수정해줘라"고 요청합니다.

**유형 2. 논리 오류 (실행은 되지만 결과가 이상함)**

어떤 입력에 어떤 결과가 나왔는지, 기대값은 무엇인지를 구체적으로 명시해서 전달합니다.

예시: "PDF를 업로드했을 때 요약이 빈 화면으로 나온다. 기대값은 3문단 요약 텍스트다."

**유형 3. Anthropic API 관련 오류**

| 오류 | 원인 | 해결 |
|---|---|---|
| `AuthenticationError` | API 키 없음 또는 잘못됨 | `.env` 파일의 `ANTHROPIC_API_KEY` 확인 |
| `RateLimitError` | 사용량 한계 도달 | 5시간 대기 후 재시도 또는 플랜 업그레이드 |
| `OverloadedError` | 서버 과부하 | 잠시 후 재시도 |
| `InvalidRequestError` | 토큰 초과 | 입력 텍스트 길이 줄이기 |

**유형 4. Claude Code 설치/실행 오류**

| 오류 | 해결 |
|---|---|
| `claude: command not found` | WinGet 또는 PowerShell 설치 재시도 |
| `Not authenticated` | `claude` 실행 후 브라우저 로그인 |
| 사용량 한계 메시지 | 5시간 대기 또는 claude.ai에서 잔여량 확인 |

### 검증 체크리스트 (제출 전 확인)

```
[ ] 모든 기능이 정상 작동하는가
[ ] API 키가 .py 코드 안에 직접 쓰여 있지 않은가
[ ] .env 파일을 .gitignore에 추가했는가
[ ] 예상치 못한 입력(빈 파일, 매우 긴 텍스트)에도 앱이 죽지 않는가
[ ] requirements.txt가 현재 사용 중인 라이브러리를 모두 포함하는가
```

requirements.txt 생성:

```
pip freeze > requirements.txt
```

---

## 5.5 최종 사용 및 배포 시 유의사항

### 개인 사용 (로컬 실행)

`.env` 파일에 API 키가 있으므로 다른 사람과 파일을 공유할 때 반드시 제외합니다. ZIP 파일로 제출할 때도 `.env`를 제외합니다.

### 온라인 배포 (Streamlit Cloud)

Streamlit Cloud를 이용하면 무료로 공개 URL에 앱을 배포할 수 있습니다.

절차 요약: GitHub 저장소를 만들고 `app.py`, `requirements.txt`, `CLAUDE.md`를 업로드합니다(`.env`는 절대 포함 금지). `https://streamlit.io/cloud`에서 GitHub 연동 후 배포합니다. Streamlit Cloud의 Secrets 메뉴에 `ANTHROPIC_API_KEY`를 입력합니다.

프로젝트 폴더에 `.gitignore` 파일을 만들고 아래 내용을 저장합니다.

```
.env
.venv/
__pycache__/
*.pyc
.DS_Store
```

### Anthropic API 키 관련 주의사항

API 키가 노출되면 계정에 과금이 발생하므로 아래를 반드시 지킵니다.

- API 키를 코드 안에 직접 쓰지 않습니다.
- 항상 `.env` 파일에 저장하고 `python-dotenv`로 로드합니다.
- GitHub에 업로드할 때 `.gitignore`에 `.env`가 포함되어 있는지 반드시 확인합니다.
- 과금 모니터링: `https://console.anthropic.com/settings/usage`

### 학술 윤리

AI가 생성한 코드를 과제로 제출할 때는 담당 교수의 AI 사용 정책을 반드시 확인합니다. AI 도움을 받은 부분을 명시하는 것을 권장합니다. 예시: "본 과제의 코드 구조는 Claude Code (Anthropic)를 활용해 생성했으며, 주요 로직과 디버깅은 직접 수행했습니다."

---

\newpage

# 6장. 고급 단계 --- Harness Engineering

## 6.1 Harness Engineering이란?

**Harness Engineering**은 AI가 생성한 코드를 자동으로 실행·테스트·평가하는 **검증 인프라(harness)를 먼저 설계하는 방법론**입니다. Claude Code가 코드를 생성하기 전에, "그 코드가 올바른지 판정하는 도구"를 먼저 만드는 것입니다.

Anthropic의 내부 연구에서도 이 접근법을 사용합니다. 에이전트가 자율적으로 코드를 수정·재실행하는 긴 작업에서, 사람이 모든 단계를 검토하는 대신 harness가 자동으로 품질을 보장합니다.

Claude Code의 2026년 Auto Mode(자동 실행 모드)도 내부적으로 harness 원리를 활용합니다. 각 도구 호출 전에 백그라운드 분류기가 안전 여부를 판단합니다.

> "기능 코드를 먼저 만들고 테스트를 나중에 추가하는 것"이 아니라,
> "테스트 기준을 먼저 정의하고 그에 맞는 코드를 생성하게 하는 것."

---

## 6.2 Harness Engineering이 필요한 시점

아래 상황 중 하나라도 해당하면 harness 설계를 먼저 해야 합니다.

- Claude Code가 생성한 코드를 수동으로 일일이 확인하기 어려울 때
- 코드 수정 후 기존 기능이 깨지는지 자동으로 확인하고 싶을 때
- 대량의 입력 데이터에 대해 결과를 자동 검사하고 싶을 때
- Claude Code에 긴 자율 작업(1시간 이상)을 맡기려 할 때
- 동일 기능의 여러 구현 방식을 비교 평가하고 싶을 때

---

## 6.3 Claude Code 기반 Harness의 기본 구조

```
[HARNESS.md -- 평가 기준(Rubric) 정의]
      |
      v
[테스트 데이터셋 (test_cases/ 폴더)]
      |
      v
[Claude Code: 기능 코드 생성]
      |
      v
[run_tests.py -- 자동 실행 및 검증]
      |
      v
[결과 리포트 (test_results.md 또는 CSV)]
      |
      v
[실패 케이스 분석 -> Claude Code에 수정 요청]
      |
      v
[재실행 -> 목표 통과율 달성 시 완료]
```

---

## 6.4 단계별 절차

### 단계 1: HARNESS.md 작성 --- 평가 기준 먼저 정의

코드를 만들기 전에 "올바른 결과란 무엇인가"를 수치와 규칙으로 정의합니다.

```markdown
# HARNESS.md

## 평가 대상
논문 요약 AI의 summarize() 함수

## 평가 기준 (Rubric)

| 기준 ID | 내용 | 가중치 | 판정 방법 |
|---|---|---|---|
| R01 | 핵심 키워드 포함 | 40% | 원문의 주요 명사 3개 이상 포함 |
| R02 | 길이 준수 | 20% | 200~500자 이내 |
| R03 | 언어 일치 | 20% | 원문 한국어면 요약도 한국어 |
| R04 | 사실 왜곡 없음 | 20% | 원문에 없는 주장 추가 여부 (LLM Judge) |

## 통과 기준
- 개별 테스트 케이스: 총점 0.7 이상 통과
- 전체 통과율 목표: 80% 이상

## 테스트 입력 규칙
- 최소 10개 케이스 준비
- 짧은 논문 (3페이지 이하), 긴 논문 (20페이지 이상), 영어 논문 포함
- 각 케이스에 expected_keywords 3개 이상 지정
```

---

### 단계 2: 테스트 데이터셋 준비

```python
# test_cases.py
TEST_CASES = [
    {
        "id": "TC001",
        "pdf_path": "test_cases/sample_short_ko.pdf",
        "expected_keywords": ["딥러닝", "이미지 분류", "정확도"],
        "expected_language": "ko",
        "expected_length_range": (200, 500),
    },
    {
        "id": "TC002",
        "pdf_path": "test_cases/sample_long_en.pdf",
        "expected_keywords": ["machine learning", "neural network", "performance"],
        "expected_language": "en",
        "expected_length_range": (200, 500),
    },
    # 최소 10개 케이스 준비
]
```

---

### 단계 3: Evaluator 함수 작성 요청

Claude Code에게 다음과 같이 요청합니다.

> "HARNESS.md의 Rubric을 기반으로 요약 결과를 자동 평가하는 `evaluate_summary(original_text, summary, expected_keywords, expected_language, expected_length_range)` 함수를 `evaluator.py`에 작성해라.
>
> 함수는 R01\~R04 각 기준별 점수(0\~1)와 총점, 실패 이유 목록을 딕셔너리로 반환해야 한다.
> R04(사실 왜곡)는 Claude API를 사용하는 LLM-as-Judge 방식으로 구현해라.
> 코드 주석은 한국어로 달아라."

---

### 단계 4: Harness 실행 스크립트 요청

> "evaluator.py와 test_cases.py를 사용해서, test_cases/의 모든 케이스를 자동 실행하고 결과를 표 형식으로 출력하는 `run_tests.py`를 작성해라.
>
> 출력 내용: 케이스별 통과/실패, 기준별 점수, 실패 이유, 전체 통과율.
> 결과를 `test_results.md`에도 저장해라."

---

### 단계 5: Claude Code로 실행

```
claude "run_tests.py를 실행하고 실패한 케이스의 원인을 분석해줘"
```

또는 직접 터미널에서:

```
python run_tests.py
```

출력 예시:

```
테스트 결과 요약 (2026-04-10)
==============================
TC001: PASS  R01=1.0 R02=1.0 R03=1.0 R04=0.8  총점=0.94
TC002: FAIL  R01=0.3 R02=1.0 R03=1.0 R04=0.9  총점=0.62
              실패 이유: R01 키워드 누락 (machine learning 포함 안됨)

전체 평균: 0.78 / 1.00
통과율: 80.0% (10개 중 8개 통과)
목표 통과율(80%) 달성: YES
```

---

### 단계 6: 실패 케이스 기반 수정 요청

> "TC002가 실패했다. 실패 이유는 R01 키워드 누락이다. 아래에 원문 일부와 현재 요약 결과를 붙여넣겠다.
>
> summarizer.py의 summarize() 함수에서 어떤 부분을 수정하면 TC002도 통과할 수 있는지 분석하고, TC001\~TC009의 점수를 낮추지 않는 범위에서 수정해라."

---

## 6.5 Claude Code 고유 Harness 기능: Hooks

Claude Code는 파일 편집, 명령 실행 전후에 자동으로 코드를 실행하는 **Hooks** 기능을 제공합니다. 이를 활용하면 harness를 코딩 루프에 자동으로 통합할 수 있습니다.

```json
// .claude/settings.json
{
  "hooks": {
    "postToolUse": [
      {
        "matcher": "edit_file|write_file",
        "type": "command",
        "command": "python run_tests.py --quick"
      }
    ]
  }
}
```

위 설정을 적용하면 Claude Code가 파일을 편집할 때마다 자동으로 테스트를 실행합니다. 테스트가 실패하면 Claude Code가 자동으로 결과를 읽고 수정을 시도합니다.

---

## 6.6 LLM-as-Judge 패턴

수치로 정의하기 어려운 품질 기준(자연스러운 문체, 창의성 등)은 Claude API 자체를 평가자로 활용합니다.

```python
# evaluator.py 중 R04(사실 왜곡 검사) 부분
import anthropic

JUDGE_SYSTEM = "당신은 텍스트 품질을 평가하는 전문가입니다. 반드시 JSON 형식으로만 응답하십시오."

JUDGE_PROMPT = """
원문과 요약을 읽고 '사실 왜곡' 여부를 판정하십시오.

[원문 일부]
{original_excerpt}

[요약]
{summary}

판정 기준:
- 원문에 없는 주장이 요약에 추가되어 있는가?
- 원문의 수치나 사실이 잘못 전달되었는가?

다음 JSON 형식으로만 응답하십시오:
{{"score": 0.0~1.0, "reason": "판정 이유"}}
(1.0 = 왜곡 없음, 0.0 = 심각한 왜곡)
"""

def judge_factual_accuracy(original_text, summary):
    client = anthropic.Anthropic()
    response = client.messages.create(
        model="claude-haiku-4-5",   # 평가용은 저렴한 모델 사용
        max_tokens=200,
        system=JUDGE_SYSTEM,
        messages=[{
            "role": "user",
            "content": JUDGE_PROMPT.format(
                original_excerpt=original_text[:1000],
                summary=summary
            )
        }]
    )
    import json
    result = json.loads(response.content[0].text)
    return result["score"], result["reason"]
```

---

## 6.7 프로젝트 규모별 Harness 권장 구성

| 규모 | 권장 구성 |
|---|---|
| 소형 (1\~2일) | HARNESS.md 작성 + 수동 테스트 5개 + assert 검사 |
| 중형 (1주) | 자동화된 evaluator + 10\~20개 테스트 케이스 + run\_tests.py |
| 대형 (2주 이상) | LLM-as-Judge + Hooks 자동화 + 결과 CSV 저장 + Claude Code 자율 수정 루프 |

---

## 6.8 Harness Engineering 전체 워크플로 요약

```
1. HARNESS.md 작성 (Rubric 정의)
         |
         v
2. 테스트 데이터셋 준비 (test_cases.py, 최소 10개)
         |
         v
3. evaluator.py 작성 (Claude Code에 요청)
         |
         v
4. 기능 코드 작성 (Claude Code로 생성)
         |
         v
5. run_tests.py 실행 -> 결과 확인
         |
         v
6. 실패 케이스 분석 -> Claude Code에 수정 요청
         |
         v
7. 재실행 -> 목표 통과율(80%+) 달성 시 완료
         |
         v
8. Hooks 설정으로 테스트 자동화 (선택)
```

---

\newpage

# 부록 A. Anthropic 플랫폼 빠른 참조표

| 항목 | Claude.ai Free | Claude.ai Pro | Claude Code (Pro 이상) |
|---|---|---|---|
| 월 요금 | 무료 | \$20 | Pro 이상 포함 |
| 설치 필요 | 없음 | 없음 | 네이티브 설치 필요 |
| 파일 직접 편집 | 불가 | 불가 | 가능 |
| 명령 자율 실행 | 불가 | 불가 | 가능 |
| 멀티 에이전트 | 불가 | 불가 | Opus 4.6 이상 |
| Git 자동 조작 | 불가 | 불가 | 가능 |
| 초보자 접근성 | 매우 쉬움 | 매우 쉬움 | 보통 |
| 권장 프로젝트 규모 | 소형 | 소형\~중형 | 중형\~대형 |

---

# 부록 B. 유용한 공식 리소스

- Claude.ai 접속: `https://claude.ai`
- Claude Code 공식 문서: `https://code.claude.com/docs`
- Claude Code 다운로드: `https://claude.com/download`
- Anthropic 콘솔 (API 관리): `https://console.anthropic.com`
- API 사용량 모니터링: `https://console.anthropic.com/settings/usage`
- Claude Code 무료 강좌 (Anthropic 공식): `https://anthropic.skilljar.com/claude-code-in-action`
- Anthropic 요금제 안내: `https://claude.com/pricing`

# =====Google 바이브 코딩 플랫폼에 대한 Gemini의 설명=====

# 1. 바이브 코딩의 개요 및 서비스 현황

바이브 코딩(Vibe Coding)은 개발자가 코드 한 줄 한 줄을 직접 타이핑하는 대신, 대규모 언어 모델(LLM)과 자연어로 소통하며 시스템의 '느낌(Vibe)'과 '구조'를 설계하여 소프트웨어를 빌드하는 새로운 방식입니다.

## 1.1 Google 기반 바이브 코딩 플랫폼
구글은 Gemini 3 시리즈를 기반으로 강력한 에이전트 기능을 활용한 바이브 코딩 환경을 제공합니다.
Gemini 기반의 바이브 코딩은 주로 다음 세 가지 환경에서 이루어집니다.

*   **Google AI Studio (Build in AI Studio):** 가장 대표적인 바이브 코딩 플랫폼입니다. 아이디어를 설명하면 AI가 코드와 파일을 생성하고, **라이브 프리뷰(Live Preview)**를 통해 즉석에서 앱을 실행해 볼 수 있습니다. (예: "스타트업 이름 생성기 만들어줘"라고 입력하면 즉시 웹 앱이 빌드됨)
*   **Gemini Code Assist (IDE 연동):** VS Code나 JetBrains 같은 전문 편집기에 설치하여 사용합니다. 기존 코드를 이해하고 대화를 통해 기능을 수정하거나 전체 파일을 변환하는 방식의 바이브 코딩을 지원합니다.
*   **Google Cloud Shell Editor:** 별도의 설정 없이 웹 브라우저에서 바로 사용할 수 있는 개발 환경으로, Gemini Code Assist가 사전 탑재되어 있어 50시간 무료 이용이 가능합니다.

| 서비스명 | 대상 및 접근 수준 | 과금 및 특징 |
| :--- | :--- | :--- |
| **Google AI Studio** | 초급 (웹 브라우저 접근) | 무료(제한적) / Pro 티어 유료. Live Preview로 즉시 앱 빌드. |
| **Gemini Code Assist** | 중급 (VS Code/IDE 플러그인) | 개인 무료 티어 제공 / 기업용 월 $19~$45. 전문 개발 환경 통합. |
| **Cloud Shell Editor** | 중급 (브라우저 내 IDE) | 50시간 무료 제공. 설치 없이 터미널과 에디터 동시 사용 가능. |

구글의 **Gemini 3** 시리즈는 강력한 **에이전트 기능(Agentic capabilities)**과 **바이브 코딩(Vibe Coding)** 능력을 갖추고 있어, 개발자가 코드 한 줄 한 줄을 직접 작성하는 대신 AI와 대화하며 애플리케이션을 빌드하고 배포하는 환경을 제공합니다.

## 2. 유료 및 무료 서비스 구분

Gemini의 코딩 서비스는 개인 사용자부터 대규모 기업까지 층위별로 나뉩니다.

### **무료 티어 (Free Tier)**
*   **대상:** 개인 개발자, 학생, 취미 개발자.
*   **포함 사항:** 
    *   **Gemini Code Assist for individuals:** VS Code, JetBrains 플러그인 무료 사용.
    *   **Gemini CLI:** 터미널 기반의 바이브 코딩 워크플로우 지원.
    *   **AI Studio:** 최신 모델(Gemini 3.1 Pro/Flash 등)을 통한 테스트 및 앱 프로토타이핑.
*   **제한:** 일일 요청 횟수(Quotas) 및 분당 호출 수(RPM) 제한이 엄격하며, 데이터가 모델 학습에 활용될 수 있습니다.

### **유료/구독 티어 (Paid Tier)**
유료 서비스는 **개인용 구독**과 **기업용 라이선스**로 나뉩니다.

| 구분 | 서비스명 | 주요 혜택 |
| :--- | :--- | :--- |
| **개인 프리미엄** | **Google AI Plus / Ultra** | **Gemini 3.1 Pro** 등 가장 성능이 뛰어난 모델에 대한 우선 접근권, 훨씬 높은 사용 할당량(Quotas) 제공. |
| **기업용 (Standard)** | **Gemini Code Assist Standard** | 월 **$19**부터 시작. 구글 클라우드 환경과 통합되며, 기업의 보안 정책을 준수(데이터 학습 제외). |
| **기업용 (Enterprise)** | **Gemini Code Assist Enterprise** | 월 **$45**부터 시작. 대규모 코드베이스 커스터마이징, 고급 보안 기능, 대규모 조직 관리 기능 포함. |

## 3. 요약: 바이브 코딩을 시작하려면?

바이브 코딩의 핵심은 **"설명하고(Describe) → 생성하고(Generate) → 실행하고(Execute) → 정교화(Refine)"**하는 루프입니다. 

*   **초보자:** **Google AI Studio**의 'Build' 기능을 통해 코딩 없이 앱을 만들어보는 것을 추천합니다.
*   **숙련자:** **Gemini Code Assist**를 IDE에 설치하여 본인의 프로젝트를 AI와 함께 대화하며 고도화하는 방식을 추천합니다.

Gemini 3 모델은 특히 복잡한 문제 해결과 에이전트 성능이 강화되어, 과거보다 훨씬 정교한 바이브 코딩이 가능해졌습니다.


# 2. 접근 절차 및 준비 사항

바이브 코딩 작업에 들어가기 전, 도구의 설정과 과업의 정의를 명확히 하는 것이 성공의 핵심입니다.


## 2.1 단계별 접근 절차

1. **인터페이스 선택:** 웹 기반(Google AI Studio, OpenAI ChatGPT)으로 시작하여 점차 IDE(Cursor, VS Code)로 확장합니다.

2. **필수 SW 및 플러그인 설치:**
   - **Cursor:** AI 네이티브 에디터로, 바이브 코딩에 가장 최적화된 도구입니다.
   - **Gemini Extension:** VS Code 내에서 구글의 코딩 어시스턴트를 호출하기 위해 필요합니다.

3. **과금 수준 확인:** 무료 티어의 할당량(Quota)을 확인하고, 대규모 프로젝트 시 API 호출 비용을 산정합니다.

## 2.2 과업 확정 방법 (Definition of Task)
AI에게 작업을 맡기기 전 다음 요소를 확정해야 합니다.

- **프로그래밍 환경:** 사용할 언어(Python, JavaScript 등)와 프레임워크(Streamlit, React 등)를 명시합니다.

- **목적 및 구조 설계:** 앱이 해결해야 할 문제와 데이터의 흐름(Input -> Process -> Output)을 정의합니다.

# 3. 작업 범위와 수준 및 한계

- **수준:** 단순한 스크립트 작성부터 풀스택 웹 애플리케이션 프로토타이핑까지 가능합니다.

- **범위:** UI 디자인, 데이터베이스 연동, 비즈니스 로직 구현을 포괄합니다.

- **한계:** AI는 매우 복잡한 대규모 아키텍처에서 논리적 일관성을 잃을 수 있으며, 보안 취약점이 포함된 코드를 생성할 가능성이 있습니다.

# 4. 바이브 코딩 작업 절차 안내

## 4.1 프롬프트 작성 원칙 및 예시
가장 간단하게로는 대화창에 프롬프트 입력만으로 가능합니다. 이때 막연한 요청으로 끝나지 말고 구체적인 페르소나와 제약 조건을 제공해야 합니다.

- **예시:** "너는 Python Streamlit 전문가야. 사용자가 업로드한 CSV 파일에서 결측치를 찾아 시각화해주는 웹 앱을 만들어줘. 디자인은 다크 모드로 설정해."


## 4.2 설계용 .md 파일 구성 및 작성 원칙
더 나아가 AI에게 복잡한 과업을 전달할 때는 별도의 `.md` 파일을 첨부하는 것이 유리합니다.
- **원칙:** 선언적(Declarative)으로 작성하되, 모호한 표현을 피하고 기술 스택을 명시합니다.
다음 내용을 적절한 이름의 .md파일에 저장하고 이 파일을 대화창에 첨부한 뒤  **"이 설계도대로 프로젝트 환경을 구축하고 코드를 작성해 줘"**라는 식으로 작업을 요청합니다.

```
# Project: AI 가계부 앱
## 1. 기능 요구사항
- 영수증 사진을 업로드하면 OCR로 금액 추출
- 월별 지출 통계 그래프 출력
## 2. 기술 스택
- 언어: Python 3.10+
- 라이브러리: Pandas, Plotly, OpenAI API
## 3. UI 구성
- 사이드바: 날짜 필터링
- 메인화면: 지출 요약 대시보드
```

위에 제시된 기능 요구사항, 기술 스택, UI 구성을 그대로 프롬프트로 사용하면, AI는 가장 일반적이고 단순한 형태의 코드를 작성합니다.

기술 스택이나 UI 구성에 포함될 내용에 대하여 사전 지식이 없다면, 미리 이런 내용들을, 예를 들어 "어떤 Python 라이브러리를 사용하는 것이 필요한가?" 등을 AI chat 창에서 질문하면서 어느 정도 사전 지식을 갖춘 다음에 이를 프롬프트에 반영합니다.

하지만 '바이브 코딩'의 완성도를 평균적인 수준을 넘어 자신의 필요에 맞추어 더욱 높이기 위해서는, 프로젝트의 성격에 따라 세부 맥락이 추가되어야 합니다.

예를 들어 이 가계부 앱의 경우에는 다음과 같은 내용들에 대하여 User가 지침을 결정해서 추가될 수 있습니다.

* 데이터 처리의 구체성: "OCR로 추출한 데이터를 어떤 형식(JSON 등)으로 저장할 것인가?" (예: 로컬 SQLite DB 사용 여부)
* 에러 핸들링: "영수증 사진이 흐릿하여 인식이 안 될 경우 사용자에게 어떤 피드백을 줄 것인가?"
* 라이브러리 버전 관리: "최신 OpenAI SDK(v1.0+) 버전을 사용할 것인가?"
* 결과물의 형태: "단일 파일(app.py)로 만들 것인가, 아니면 기능별로 파일을 분리할 것인가?"

**[학생 입장에서 현실적인 프롬프트 입력 과정]** 

1. 반복적, 대화형 프롬프트 입력

학생들은 물론이고, 현업 개발자들조차도 가장 기본적인 요구사항을 ***'기본 뼈대'**로 삼되, AI와 대화를 주고받으며(Iterative process) 살을 붙여나가는 과정이 필요합니다.

프로젝트의 모든 세부 작동 과정을 머릿 속에 그릴 수 있는 사전 업역 지식(domain knowledge)이 없는 한, 첫 프롬프트는 대개 중요한 구체사항들이 누락될 수 있습니다.
현실적으로는, 학생이 구상할 수 있는 가능한 범위 내에서 첫 프롬프트로 작업을 시작하고, 그 뒤 이 앱을 실행하는 과정에서 계속해서 부족한 점이나 에러가 등장하게 되면, 그때마다 AI와 계속 대화하면서 부족한 점을 계속 채워넣고 에러가 발생하는 부분을 수정해 나가는 전략을 취할 필요가 있습니다.

2. 프롬프트 구문 자체를  AI에 요구

많은 학생들이 예를 들어 당장 "학습 진도 관리 앱"을 만들고싶어 해도 막상, 프롬프트를 어떻게 입력해야 할지, 구체적인 지시 사항을 어떻게 서술해야 할지, 막막하게 느낄 수 있습니다.
이럴 떄에는 **"나는 대학생이고 AI 바이브 코딩 초보자야. 나는 학기 중 수강하는 과목들에 대해 학습 진도를 관리하는 앱을 만들고 싶어. 그런데 나는 프롬프트를 어떻게 작성해야 할지 모르는 상태이니, 적절한 프롬프트 문안을 작성해줘."** 로 시작해서 여러 차례 대화를 통해 프롬프트 문안을 완성하는 것도 좋은 방법입니다.

가계부 앱 외에 프로젝트 예시를 몇 가지 더 들면 다음과 같습니다.

## 예시 A: AI 기반 개인 맞춤형 운동 루틴 생성기
단순한 운동 목록 나열이 아니라, 사용자의 체격 조건과 목표를 분석하여 시각화된 계획을 제공하는 프로젝트입니다.

* **1. 기능 요구사항:**
    * 사용자의 키, 몸무게, 운동 목적(다이어트/근비대) 입력 폼.
    * LLM을 활용하여 주간 운동 스케줄 및 식단 가이드 생성.
    * 운동 부위별 비중을 파이 차트(Pie Chart)로 시각화.
* **2. 기술 스택:**
    * 언어: Python 3.10+
    * 프레임워크: Streamlit (빠른 UI 구현)
    * 시각화: Matplotlib 또는 Seaborn
* **3. UI 구성:**
    * 입력창: 슬라이더와 선택 박스로 구성된 신체 정보 입력.
    * 결과창: 탭(Tab) 구성을 통해 '운동 계획'과 '영양 가이드' 분리 표시.

## 예시 B: 뉴스 요약 및 감성 분석 대시보드
특정 키워드를 검색하면 최신 뉴스를 가져와 요약하고, 해당 뉴스가 긍정적인지 부정적인지 분석해 주는 프로젝트입니다.

* **1. 기능 요구사항:**
    * 특정 키워드(예: '생성형 AI') 검색 시 관련 뉴스 크롤링 또는 API 호출.
    * 각 뉴스 기사의 핵심 내용을 3줄로 요약.
    * 뉴스 전체의 감성 상태(Sentiment)를 점수화하여 게이지 차트로 표시.
* **2. 기술 스택:**
    * 언어: Python
    * 도구: BeautifulSoup (크롤링) 또는 NewsAPI
    * 분석: OpenAI GPT-4o (요약 및 감성 분석)
* **3. UI 구성:**
    * 상단: 키워드 입력창과 검색 버튼.
    * 중단: 주요 뉴스 카드 리스트.
    * 하단: 전체 뉴스 흐름을 보여주는 감성 지수 그래프.

## 4.3 디버깅 및 배포 유의 사항
- **디버깅:** 처음 AI가 생성해준 코드를 실행하다보면 에러 메시지를 만날 확률이 높습니다. 이 에러 메시지를, 텍스트 Ctrl+C 하거나 화면캡처한 이미지(이미지는 텍스트보다 토큰을 더 많이 사용함에 유의!)를 그대로 AI에게 복사하여 붙여넣고 원인 분석과 해결책을 요청합니다. **"[에러 첨부 후] 원인을 분석하고 해결책을 제시해줘!"** 
- **배포: ** API 키와 같은 민감 정보는 반드시 `.env` 파일에 격리하고, 배포 전 AI가 생성한 코드의 라이선스를 확인합니다. 학생이 과제 형태로 작성한 앱은 학생이 개인 용도로만 사용하면 큰 문제가 없다. 그러나 이를 제3자에게 공유하거나 상업용으로 활용하려고 한다면 라이선스, 네트워크 설정, 보안 설정, 과금 설계 등에서 차원이 다른 매우 복잡한 이슈가 등장합니다. 이런 내용에 대해서는 다시 AI에 앱에 대한 정보를 다양하게 제시한 뒤, 어떤 조치를 취해야 할지 반드시 사전 점검하고 이르 반영한 뒤 배포하여야 한다.  


# 5. 최상위 단계: Harness Engineering (하네스 엔지니어링)

하네스 엔지니어링은 AI가 단순히 코드를 생성하는 것에서 나아가, 그 코드가 올바른지 (사람 개입 없이 AI가) 스스로 검증하고 수정하게 만드는 자동화된 환경을 구축하는 것입니다. 
이 작업은 대규모 상업용 또는 기업 프로젝트를 실행하는 전문 개발자 직군에서 수행하는 것이 관행이나, 개인 용도의 앱을 제작하는 경우에도 충분히 적용할 수 있다.
하네스 엔지니어링에 대한 상세한 지침, 그리고 그 장단점과 유의사항에 대해서는 별도의 지식 영역이므로, AI에 세부 질문 또는 전문 지침서를 통해 충분히 학습하고 임할 것을 권합니다.

1. **테스트 하네스 설계:** AI에게 코드와 함께 해당 코드를 검증할 '유닛 테스트(Unit Test)' 코드를 동시에 작성하게 합니다.
2. **자기 수정 루프(Self-Correction Loop):** 테스트 코드 실행 결과(에러 로그)를 다시 AI에게 피드백으로 주어, AI가 스스로 코드를 고치게 만드는 반복 프로세스를 설정합니다.
3. **지속적 통합:** 검증된 모듈을 기존 시스템에 안전하게 결합하는 파이프라인을 구축하여 에이전트 중심의 개발을 완성합니다.
