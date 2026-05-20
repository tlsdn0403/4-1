---
title: "GPTs Web Minimum Guide"
author: "Song Kyungmo, Tech University of Korea"
date: "2026-04-08"
fontsize: 11pt
mainfont: "Malgun Gothic"
sansfont: "Malgun Gothic"
monofont: "Consolas"
CJKmainfont: "Malgun Gothic"
CJKsansfont: "Malgun Gothic"
geometry:
  - margin=1in
header-includes:
  - \usepackage{xeCJK}
  - \setCJKmainfont{Malgun Gothic}
  - \setCJKsansfont{Malgun Gothic}
  - \setmonofont{Consolas}
---


# ChatGPT 웹에서 GPTs 구축하기: 초급 가이드

## 0. GPTs와 API 기반 Agentic AI의 차이

학생들이 헷갈리기 쉬운 부분이므로 간단히 구분해 줄 필요가 있다.

* **GPTs**: ChatGPT 안에서 만드는 무코드 도구(웹 화면 왼쪽 네비게이션 창에 GPT로 표시)
* **API 기반 Agentic AI 코딩**: Python 등으로 외부 프로그램 안에 AI 기능을 넣는 방식

OpenAI 도움말도 GPTs는 **ChatGPT 안에서 사용하는 no-code assistant**이고, 외부 웹사이트나 서비스에 넣는 방식은 **API 사용 영역**이라고 설명한다. ([OpenAI Help Center][3])

즉, GPTs는 **입문 단계**, API는 **개발 단계**라고 이해하면 된다.

---

## 0. 수업용 한 줄 정리

학생들에게는 이렇게 정리하면 된다.

> GPTs는 “매번 긴 프롬프트를 다시 쓰지 않도록, 역할·자료·출력방식을 미리 세팅한 전용 ChatGPT”이다. 먼저 GPTs로 작업 구조를 설계해 보고, 그다음 필요할 때 API 프로그래밍으로 넘어가는 것이 자연스러운 학습 경로다. 

---

## 1. GPTs란 무엇인가

GPTs(커스텀 GPT)는 **특정 목적에 맞게 미리 성격, 지시사항, 참고자료, 기능을 설정해 둔 맞춤형 ChatGPT**이다. 일반 채팅과 달리, 매번 긴 프롬프트를 다시 입력하지 않아도 같은 목적의 작업을 반복적으로 수행하게 만들 수 있다. OpenAI 도움말에 따르면 GPT는 **instructions, knowledge, capabilities** 등을 조합해 특정 용도로 맞춤화한 버전의 ChatGPT이다. ([OpenAI Help Center][1])

쉽게 말하면 다음과 같다.

* **일반 채팅**: 그때그때 일회성으로 질문
* **GPTs**: 특정 역할과 작업 절차를 미리 세팅해 둔 전용 도구

예를 들어 다음과 같은 GPT를 만들 수 있다.

* 대학 과제 피드백 GPT
* 논문 요약 GPT
* 한국어→영어 번역 GPT
* 발표문 초안 작성 GPT
* 특정 강의 전용 튜터 GPT

---

## 2. 누가 만들 수 있는가

OpenAI 도움말 기준으로, **GPT 생성 기능은 ChatGPT Pro, Plus, Team, Enterprise, Edu 사용자에게 제공**된다. 반면 GPT를 사용하는 범위나 공유 방식은 플랜과 워크스페이스 정책에 따라 달라질 수 있다. ([OpenAI Help Center][2])

따라서 학생들에게는 먼저 다음을 확인하게 하면 된다.

* 본인의 ChatGPT 계정이 GPT 생성 가능 플랜인지
* 학교나 기관 계정이라면 워크스페이스에서 GPT 생성이 허용되는지

---

## 3. GPT를 만드는 기본 절차

OpenAI 도움말의 공식 흐름은 대체로 다음과 같다. **GPTs 영역으로 이동 → Create 선택 → 대화형 또는 편집기 방식으로 설정 → Preview에서 테스트 → Save** 순서이다. ([OpenAI Help Center][3])

학생용으로 더 쉽게 풀어 쓰면 다음 7단계다.

### 1단계. ChatGPT 왼쪽 내비게이션에서 GPTs 영역으로 이동

웹 브라우저에서 ChatGPT를 연 뒤, 왼쪽 사이드바에서 **GPTs** 또는 이에 해당하는 메뉴로 들어간다. 공식 도움말도 “Open the GPTs area in ChatGPT”라고 안내한다. ([OpenAI Help Center][3])

### 2단계. Create 버튼 선택

GPTs 화면에서 **Create**를 눌러 새 GPT 생성을 시작한다. ([OpenAI Help Center][3])

### 3단계. 만드는 방식 선택

GPT는 두 방식으로 만들 수 있다.

* **대화형 빌드**: “나는 이런 GPT를 만들고 싶다”라고 자연어로 설명하면서 생성
* **편집기 직접 설정**: 이름, 설명, 지시문, 기능 등을 직접 입력

OpenAI 도움말도 GPT는 **conversationally built** 하거나 **configured directly in the editor** 할 수 있다고 설명한다. ([OpenAI Help Center][3])

### 4단계. 핵심 항목 입력

초급 단계에서는 최소한 다음 4가지를 채워야 한다.

* **이름(Name)**: GPT의 용도 드러나게
* **설명(Description)**: 어떤 일을 하는 GPT인지 한 줄 요약
* **지시사항(Instructions)**: 어떻게 답해야 하는지
* **대화 스타터(Conversation starters)**: 사용 예시 질문

특히 가장 중요한 것은 **Instructions**이다. 이 부분이 GPT의 역할, 말투, 작업 절차, 출력 형식을 사실상 결정한다. OpenAI 도움말도 GPT 편집에서 instructions, knowledge, capabilities 등을 설정한다고 명시한다. ([OpenAI Help Center][4])

### 5단계. 필요하면 자료 업로드

관련 문서나 참고 파일이 있다면 **Knowledge**에 업로드할 수 있다. 이 기능을 쓰면 GPT가 해당 자료를 바탕으로 답하도록 유도할 수 있다. ([OpenAI Help Center][4])

예:

* 강의계획서 PDF
* 과제 안내문
* 회사 소개 자료
* 논문 원문
* 스타일 가이드 문서

### 6단계. 필요 기능 활성화

GPT 편집 화면에서는 기능을 켜고 끌 수 있다. 현재 도움말 기준으로 예시 기능에는 **Web search, Image generation, Canvas, Code Interpreter & Data Analysis, Apps** 등이 포함된다. 다만 실제 표시 항목은 계정, 지역, 워크스페이스 설정에 따라 달라질 수 있다. ([OpenAI Help Center][2])

초급 학생에게는 보통 다음 정도만 설명하면 충분하다.

* **Web search**: 최신 정보 검색
* **Image generation**: 이미지 생성
* **Code Interpreter / Data Analysis**: 계산, 데이터 분석, 파일 처리

### 7단계. Preview로 테스트 후 저장

공식 도움말은 설정 후 **Preview에서 테스트하고 Save** 하라고 안내한다. 수정 후 다시 저장하면 버전 관리도 가능하다. ([OpenAI Help Center][3])

---

## 4. 학생들에게 가르칠 때 가장 중요한 설계 원칙

초보자는 기능 버튼보다도 **설계 문장**을 잘 쓰는 훈련이 더 중요하다. GPT의 품질은 대체로 다음 요소에서 갈린다.

### A. 역할을 좁게 잡기

나쁜 예:

* “무엇이든 다 도와주는 만능 GPT”

좋은 예:

* “대학생의 발표문 초안을 만드는 GPT”
* “강의자료 PDF를 바탕으로 핵심 개념을 설명하는 GPT”

역할이 좁을수록 결과가 안정적이다.

### B. 목적을 한 문장으로 명확히 쓰기

예:

* “이 GPT는 학생이 업로드한 강의자료를 바탕으로 시험 대비 요약본을 만든다.”

### C. 출력 형식을 지정하기

예:

* “항상 한국어로 답하라.”
* “개조식 5개 항목으로 정리하라.”
* “표 대신 번호 목록을 사용하라.”
* “먼저 요약, 다음에 예시, 마지막에 주의점 순으로 답하라.”

### D. 금지사항을 명시하기

예:

* “자료에 없는 사실을 단정하지 마라.”
* “확실하지 않으면 추정이라고 표시하라.”
* “학생 대신 과제를 완성하지 말고 초안과 피드백 중심으로 도와라.”

이런 금지 규칙이 없으면 GPT가 과장하거나 불필요하게 창작하는 경향이 생긴다.

---

## 5. 초급 학생용 권장 작성 틀

학생들에게 아래 틀을 그대로 복사해 쓰게 하면 좋다.

### GPT 이름

예:
**대학생 발표문 코치 GPT**

### 설명

예:
**학생의 발표 주제를 정리하고 3~5분 발표문 초안을 만드는 도우미**

### Instructions 예시

```text
너는 대학생 발표 준비를 돕는 튜터다.
항상 한국어로 답하라.
사용자가 제시한 주제를 먼저 3~5개 핵심 포인트로 정리하라.
그 다음 3분 발표용 초안을 작성하라.
문장은 너무 길지 않게 쓰고, 어려운 용어는 쉬운 말로 풀어라.
불확실한 정보는 단정하지 말고, 추정임을 표시하라.
표보다 번호 목록을 우선 사용하라.
사용자가 수정 요청을 하면 전체를 다시 쓰지 말고 수정된 부분만 분리해서 보여줘라.
```

### Conversation starters 예시

* “내 발표 주제를 3분 발표문으로 만들어줘.”
* “이 문단을 발표용 말투로 바꿔줘.”
* “이 주제의 핵심 논점을 5개만 정리해줘.”

이 정도만으로도 초급용 GPT는 충분히 작동한다.

---

## 6. 초급 실습 과제 예시

수업에서는 너무 복잡한 GPT보다 다음 3종 중 하나를 만들게 하는 것이 적절하다.

### 실습 A. 강의자료 요약 GPT

목적:

* 업로드한 PDF를 바탕으로 핵심 개념 요약
* 시험 대비 예상 질문 생성

### 실습 B. 번역 및 문장 다듬기 GPT

목적:

* 한영 번역
* 어색한 문장 수정
* 발표문 말투 정리

### 실습 C. 글쓰기 피드백 GPT

목적:

* 서론/본론/결론 구조 점검
* 중복 표현 제거
* 논리 흐름 피드백

이 셋은 **자료 업로드, 지시문 작성, 출력 형식 지정**을 모두 연습하기 좋다.

---

## 7. 학생들이 자주 하는 실수

### 실수 1. 지시가 너무 짧음

예:

* “친절하게 답해줘.”

이 정도로는 부족하다.
무엇을, 누구를 위해, 어떤 형식으로 답할지 써야 한다.

### 실수 2. 역할이 너무 많음

예:

* 번역도 하고, 코딩도 하고, 그림도 그리고, 논문도 쓰고, 상담도 하는 GPT

초급 단계에서는 한 GPT에 한 목적이 낫다.

### 실수 3. 참고자료 없이 정확한 답을 기대함

자료 기반 답변이 필요하면 문서를 업로드해야 한다. 그렇지 않으면 일반 지식 기반으로 답할 가능성이 크다.

### 실수 4. 테스트를 안 하고 바로 저장함

OpenAI도 Preview 테스트를 권장한다. 저장 전에 반드시 3~5개의 대표 질문으로 시험해 봐야 한다. ([OpenAI Help Center][4])

---



[1]: https://help.openai.com/en/articles/8554407-gpts-in-chatgpt?utm_source=chatgpt.com "GPTs in ChatGPT"
[2]: https://help.openai.com/pt-pt/articles/8554397-creating-a-gpt?utm_source=chatgpt.com "Creating a GPT | OpenAI Help Center"
[3]: https://help.openai.com/pt-pt/articles/8798889-how-can-i-use-gpts?utm_source=chatgpt.com "How can I use GPTs? - OpenAI Help Center"
[4]: https://help.openai.com/en/articles/8554397-creating-and-editing-gpts?utm_source=chatgpt.com "Creating and editing GPTs"
