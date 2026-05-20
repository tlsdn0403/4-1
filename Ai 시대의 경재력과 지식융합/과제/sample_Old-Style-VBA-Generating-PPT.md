```
Option Explicit

' =========================
' CONFIG
' =========================
Private Const TITLE_FONT As String = "Aptos Display"
Private Const BODY_FONT  As String = "Aptos"
Private Const TITLE_SIZE As Single = 30
Private Const BODY_SIZE  As Single = 18

Private Const ORANGE_RGB As Long = 49407 ' approx #FF9F00-ish (BGR in VBA is tricky; this is a decent orange)
Private Const LIGHT_GRAY As Long = 15198183

' Slide layout helpers (in points)
Private Const M_LEFT As Single = 40
Private Const M_TOP As Single = 30
Private Const M_RIGHT As Single = 40
Private Const M_BOTTOM As Single = 30

' =========================
' ENTRY POINT
' =========================
Public Sub BuildCourseDeck()
    Dim pres As Presentation
    Set pres = Application.Presentations.Add
    
    ' Use 16:9
    pres.PageSetup.SlideSize = ppSlideSizeOnScreen16x9
    
    ' 1) Cover slide
    AddCoverSlide pres, _
        "AI 시대의 경쟁력과 지식 융합", _
        "한국공학대학교", _
        "담당교수: 송경모", _
        "2026-03-04"
    
    ' 2) Early structure slides (from TXT)
    AddBulletsSlide pres, "AI 시대의 경쟁력과 지식 융합", Array( _
        "강좌 개요(Overview)", _
        "비전공자 핵심 소양 교육", _
        "DX를 넘어 AX 시대를 대비함", _
        "융합형 교육 과정", _
        "비판적 성찰 능력" _
    )
   
    AddBulletsSlideWithLabel pres, "교육 목표 및 기대 효과", "학습 목표(Goal)", Array( _
        "AI 기술 원리 직관적 이해", _
        "인문·사회·공학 지식 융합", _
        "사람의 고유 경쟁력", _
        "지식 자본가로 성장" _
    )
    
    AddBulletsSlideWithLabel pres, "참고도서 및 소스 정보", "주교재(Main Book)", Array( _
        "AI  앞에 선 경영자의 선택 리버럴 아트(트로이목마 출판사, 2024", _
        "피터 드러커 경영 사상과 인문학 융합 지식 기반", _
        "웹사이트: https://product.kyobobook.co.kr/detail/S000214718498", _
        "한국공학대학교도서관 소장 중" _
    )
    
    ' 3) Weekly schedule slides (from weekly-class.pdf)
    AddWeeklyScheduleSlides pres
    
    ' 4) Grading slide (table 2 cols, 6 rows)
    AddGradingSlide pres
    
    ' 5) Attendance slide
    AddBulletsSlideWithLabel pres, "출석 및 감점 규정", "출결 관리(Attendance)", Array( _
        "전자출석(유체크) 실시", _
        "결석 1/4 이상 시 자동 F", _
        "결석 1회: -2점", _
        "지각 1회: -1점", _
        "출튀 적발: 즉시 F" _
    )
    
    ' 6) Project slide
    AddBulletsSlideWithLabel pres, "주요 과제물 안내", "프로젝트(Project)", Array( _
        "Agentic AI 또는 앱 구축", _
        "3분 이내 숏폼 영상 제작", _
        "자유 관심 대상 선정", _
        "제작 경험 공유 및 발표" _
    )
    
    ' 7) Content topic slides (examples: AI evolution + diagram/table/discussion)
    AddAIevolutionBlock pres
    AddAutonomousDrivingBlock pres
    AddEcommerceBlock pres
    
    ' (You can continue adding the remaining topic blocks the same way.)
    
    ' Save
    Dim outPath As String
    outPath = "D:\70_Workspace\tukorea\D:\70_Workspaces\tukorea\20260304_aSKM_tWeek01-Lecture_oTUKOREA_fPres_v00.pptm"
    pres.SaveAs outPath

    MsgBox "Done. Saved to: " & outPath, vbInformation
    
End Sub

' =========================
' SLIDE BUILDING PRIMITIVES
' =========================
Private Sub AddCoverSlide(ByVal pres As Presentation, _
                          ByVal titleText As String, _
                          ByVal univ As String, _
                          ByVal prof As String, _
                          ByVal dt As String)
    Dim sld As Slide
    Set sld = pres.Slides.Add(pres.Slides.Count + 1, ppLayoutBlank)
    
    Dim W As Single, H As Single
    W = pres.PageSetup.SlideWidth
    H = pres.PageSetup.SlideHeight
    
    Dim shpTitle As Shape
    Set shpTitle = sld.Shapes.AddTextbox(msoTextOrientationHorizontal, M_LEFT, 150, W - M_LEFT - M_RIGHT, 80)
    With shpTitle.TextFrame2.TextRange
        .Text = titleText
        .Font.Name = TITLE_FONT
        .Font.Size = 44
        .Font.Bold = msoTrue
    End With
    
    Dim shpMeta As Shape
    Set shpMeta = sld.Shapes.AddTextbox(msoTextOrientationHorizontal, M_LEFT, 260, W - M_LEFT - M_RIGHT, 120)
    With shpMeta.TextFrame2.TextRange
        .Text = univ & vbCrLf & prof & vbCrLf & "날짜: " & dt
        .Font.Name = BODY_FONT
        .Font.Size = 22
    End With
End Sub

Private Sub AddBulletsSlide(ByVal pres As Presentation, ByVal titleText As String, ByVal bullets As Variant)
    Dim sld As Slide
    Set sld = pres.Slides.Add(pres.Slides.Count + 1, ppLayoutBlank)
    
    AddTitle sld, pres, titleText
    
    Dim W As Single, H As Single
    W = pres.PageSetup.SlideWidth
    H = pres.PageSetup.SlideHeight
    
    Dim shp As Shape
    'Reduce the width of body to 2/3
    Set shp = sld.Shapes.AddTextbox(msoTextOrientationHorizontal, M_LEFT, 120, bodyWidth, H - 160)
    'Set shp = sld.Shapes.AddTextbox(msoTextOrientationHorizontal, M_LEFT, 120, W - M_LEFT - M_RIGHT, H - 160)
    With shp.TextFrame2
        .WordWrap = msoTrue
        .AutoSize = msoAutoSizeNone
        .TextRange.Font.Name = BODY_FONT
        .TextRange.Font.Size = BODY_SIZE
        .TextRange.ParagraphFormat.Bullet.Visible = msoTrue
        .MarginLeft = 10
        .MarginRight = 10
        .MarginTop = 8
        .MarginBottom = 8
    End With
    
    Dim i As Long, txt As String
    txt = ""
    For i = LBound(bullets) To UBound(bullets)
        txt = txt & CStr(bullets(i)) & vbCrLf
    Next i
    shp.TextFrame2.TextRange.Text = txt
End Sub

Private Sub AddBulletsSlideWithLabel(ByVal pres As Presentation, ByVal titleText As String, ByVal labelText As String, ByVal bullets As Variant)
    Dim sld As Slide
    Set sld = pres.Slides.Add(pres.Slides.Count + 1, ppLayoutBlank)
    
    AddTitle sld, pres, titleText
    
    Dim W As Single, H As Single
    W = pres.PageSetup.SlideWidth
    H = pres.PageSetup.SlideHeight
    
    ' Label box (square box)
    Dim label As Shape
    Set label = sld.Shapes.AddShape(msoShapeRectangle, M_LEFT, 95, 260, 34)
    With label
        .Fill.ForeColor.RGB = LIGHT_GRAY
        .Line.ForeColor.RGB = 10066329
        .TextFrame2.TextRange.Text = labelText
        With .TextFrame2.TextRange.Font
            .Name = BODY_FONT
            .Size = 16
            .Bold = msoTrue
        End With
        .TextFrame2.MarginLeft = 10
        .TextFrame2.MarginRight = 10
    End With
    
    ' Bullets
    Dim shp As Shape
    Set shp = sld.Shapes.AddTextbox(msoTextOrientationHorizontal, M_LEFT, 145, W - M_LEFT - M_RIGHT, H - 185)
    With shp.TextFrame2
        .WordWrap = msoTrue
        .AutoSize = msoAutoSizeNone
        .TextRange.Font.Name = BODY_FONT
        .TextRange.Font.Size = BODY_SIZE
        .TextRange.ParagraphFormat.Bullet.Visible = msoTrue
        .MarginLeft = 10
        .MarginRight = 10
        .MarginTop = 8
        .MarginBottom = 8
    End With
    
    Dim i As Long, txt As String
    txt = ""
    For i = LBound(bullets) To UBound(bullets)
        txt = txt & CStr(bullets(i)) & vbCrLf
    Next i
    shp.TextFrame2.TextRange.Text = txt
End Sub

Private Sub AddTitle(ByVal sld As Slide, ByVal pres As Presentation, ByVal titleText As String)
    Dim W As Single
    W = pres.PageSetup.SlideWidth
    
    Dim t As Shape
    Set t = sld.Shapes.AddTextbox(msoTextOrientationHorizontal, M_LEFT, 30, W - M_LEFT - M_RIGHT, 60)
    With t.TextFrame2.TextRange
        .Text = titleText
        .Font.Name = TITLE_FONT
        .Font.Size = TITLE_SIZE
        .Font.Bold = msoTrue
    End With
End Sub

' =========================
' WEEKLY SCHEDULE (weekly-class.pdf)
' Each week = one card slide
' =========================
Private Sub AddWeeklyScheduleSlides(ByVal pres As Presentation)
    ' Source content extracted from weekly-class.pdf page 1:
    ' Week 1–7 topics, Week 8 midterm, Week 9–12 topics, Week 13–14 presentations, Week 15 final. :contentReference[oaicite:5]{index=5}
    
    Dim weeks(1 To 15) As String
    Dim details(1 To 15) As String
    Dim prep(1 To 15) As String
    
    weeks(1) = "1주차"
    details(1) = "강의 소개. 교재 1. AI 현상 개요 I" & vbCrLf & _
                 "자율주행, 유통, 교육, 예술 등 산업 전반 사례 분석"
    prep(1) = "학습준비사항: 없음"
    
    weeks(2) = "2주차"
    details(2) = "교재 2. AI 현상 개요 II" & vbCrLf & _
                 "공급 형태 분류(폐쇄형/개방형, 온프레미스/클라우드) 및 오남용 위험(환각, 모델 붕괴, 편향) 개관"
    prep(2) = "학습준비사항: 교재 예습"
    
    weeks(3) = "3주차"
    details(3) = "교재 3. AI의 역사 I: 태동부터 딥러닝까지" & vbCrLf & _
                 "기호주의 vs 연결주의, 머신러닝 발전, 딥러닝까지 핵심 원리(비전공자 수준)"
    prep(3) = "학습준비사항: 교재 예습"
    
    weeks(4) = "4주차"
    details(4) = "교재 4. AI의 역사 II: LLM의 등장" & vbCrLf & _
                 "트랜스포머(transformer) 등장과 LLM 작동 원리"
    prep(4) = "학습준비사항: 교재 예습"
    
    weeks(5) = "5주차"
    details(5) = "교재 5. AI의 역사 III: LLM 이후" & vbCrLf & _
                 "멀티모달 LLM 개념/원리, 효과적 프롬프트 작성 원칙"
    prep(5) = "학습준비사항: 교재 예습"
    
    weeks(6) = "6주차"
    details(6) = "교재 6. AI 생태계의 현재와 미래 I" & vbCrLf & _
                 "LLM 추론/기억, RAG 개요, Agentic AI 등장과 의미"
    prep(6) = "학습준비사항: 교재 예습"
    
    weeks(7) = "7주차"
    details(7) = "교재 7. AI 생태계의 현재와 미래 II" & vbCrLf & _
                 "바이브 코딩(vibe coding) 원리, 전력/데이터센터 현황, 미래 견해"
    prep(7) = "학습준비사항: 교재 예습"
    
    weeks(8) = "8주차"
    details(8) = "중간고사"
    prep(8) = ""
    
    weeks(9) = "9주차"
    details(9) = "교재 8. AI와 사회경제의 변화" & vbCrLf & _
                 "분업/자본/노동 의미, 조직 구조 변화, AI 전환 문제, 기업가정신과 AI 창업"
    prep(9) = "학습준비사항: 교재 예습"
    
    weeks(10) = "10주차"
    details(10) = "교재 9. AI시대의 법과 제도" & vbCrLf & _
                  "지식재산권, 프라이버시, 고위험 AI 대응 현황 + 법철학/민주주의 영향"
    prep(10) = "학습준비사항: 교재 예습"
    
    weeks(11) = "11주차"
    details(11) = "교재 10. AI 시대의 Liberal Arts 지식" & vbCrLf & _
                  "리버럴 아트/인문학 중요성, 지식 노동 의미 변화"
    prep(11) = "학습준비사항: 참고도서 일부 열람"
    
    weeks(12) = "12주차"
    details(12) = "교재 11. AI와 철학적 성찰" & vbCrLf & _
                  "지능/주체성/창의성 의미(철학·심리학), 지식노동자·학생 학습/훈련 방향"
    prep(12) = "학습준비사항: 교재 예습"
    
    weeks(13) = "13주차"
    details(13) = "과제 발표 1회차" & vbCrLf & _
                  "Agentic AI 설계 또는 바이브 코딩 앱 제작 → 3분 숏폼 영상 제작/발표"
    prep(13) = ""
    
    weeks(14) = "14주차"
    details(14) = "과제 발표 2회차 (13주차 발표 연속)"
    prep(14) = ""
    
    weeks(15) = "15주차"
    details(15) = "기말고사"
    prep(15) = ""
    
    Dim i As Long
    For i = 1 To 15
        AddWeeklyCardSlide pres, weeks(i), details(i), prep(i)
    Next i
End Sub

Private Sub AddWeeklyCardSlide(ByVal pres As Presentation, ByVal weekTitle As String, ByVal mainText As String, ByVal prepText As String)
    Dim sld As Slide
    Set sld = pres.Slides.Add(pres.Slides.Count + 1, ppLayoutBlank)
    
    AddTitle sld, pres, "주차별 강의 일정"
    
    Dim W As Single, H As Single
    W = pres.PageSetup.SlideWidth
    H = pres.PageSetup.SlideHeight
    
    ' Card background
    Dim card As Shape
    Set card = sld.Shapes.AddShape(msoShapeRoundedRectangle, M_LEFT, 120, W - M_LEFT - M_RIGHT, H - 170)
    With card
        .Fill.ForeColor.RGB = RGB(245, 246, 250)
        .Line.ForeColor.RGB = RGB(220, 222, 230)
        .Line.Weight = 1.25
    End With
    
    ' Week header
    Dim hdr As Shape
    Set hdr = sld.Shapes.AddTextbox(msoTextOrientationHorizontal, M_LEFT + 20, 140, W - M_LEFT - M_RIGHT - 40, 40)
    With hdr.TextFrame2.TextRange
        .Text = weekTitle
        .Font.Name = TITLE_FONT
        .Font.Size = 28
        .Font.Bold = msoTrue
    End With
    
    ' Main text
    Dim body As Shape
    Set body = sld.Shapes.AddTextbox(msoTextOrientationHorizontal, M_LEFT + 20, 190, W - M_LEFT - M_RIGHT - 40, H - 280)
    With body.TextFrame2
        .WordWrap = msoTrue
        .TextRange.Text = mainText
        .TextRange.Font.Name = BODY_FONT
        .TextRange.Font.Size = BODY_SIZE
    End With
    
    ' Prep text (small footer)
    If Len(prepText) > 0 Then
        Dim foot As Shape
        Set foot = sld.Shapes.AddTextbox(msoTextOrientationHorizontal, M_LEFT + 20, H - 120, W - M_LEFT - M_RIGHT - 40, 30)
        With foot.TextFrame2.TextRange
            .Text = prepText
            .Font.Name = BODY_FONT
            .Font.Size = 16
            .Font.Italic = msoTrue
        End With
    End If
End Sub

' =========================
' GRADING SLIDE (TXT spec)
' =========================
Private Sub AddGradingSlide(ByVal pres As Presentation)
    Dim sld As Slide
    Set sld = pres.Slides.Add(pres.Slides.Count + 1, ppLayoutBlank)
    
    AddTitle sld, pres, "성적 평가 방식 안내"
    
    Dim W As Single, H As Single
    W = pres.PageSetup.SlideWidth
    H = pres.PageSetup.SlideHeight
    
    ' Label box
    Dim label As Shape
    Set label = sld.Shapes.AddShape(msoShapeRectangle, M_LEFT, 95, 260, 34)
    With label
        .Fill.ForeColor.RGB = LIGHT_GRAY
        .Line.ForeColor.RGB = 10066329
        .TextFrame2.TextRange.Text = "평가 기준(Grading)"
        With .TextFrame2.TextRange.Font
            .Name = BODY_FONT
            .Size = 16
            .Bold = msoTrue
        End With
        .TextFrame2.MarginLeft = 10
        .TextFrame2.MarginRight = 10
    End With
    
    Dim tblShape As Shape
    Set tblShape = sld.Shapes.AddTable(6, 2, M_LEFT, 150, W - M_LEFT - M_RIGHT, 240)
    
    Dim tbl As Table
    Set tbl = tblShape.Table
    
    Dim items As Variant
    items = Array( _
        Array("과제물", "25%"), _
        Array("출석", "25%"), _
        Array("중간고사", "25%"), _
        Array("기말고사", "15%"), _
        Array("퀴즈", "10%"), _
        Array("합계", "100%") _
    )
    
    Dim r As Long
    For r = 1 To 6
        tbl.Cell(r, 1).Shape.TextFrame2.TextRange.Text = items(r - 1)(0)
        tbl.Cell(r, 2).Shape.TextFrame2.TextRange.Text = items(r - 1)(1)
        
        StyleTableCell tbl.Cell(r, 1).Shape, False
        StyleTableCell tbl.Cell(r, 2).Shape, False
    Next r
    
    ' Emphasize last row
    StyleTableCell tbl.Cell(6, 1).Shape, True
    StyleTableCell tbl.Cell(6, 2).Shape, True
End Sub

Private Sub StyleTableCell(ByVal cellShape As Shape, ByVal isBold As Boolean)
    With cellShape.TextFrame2.TextRange.Font
        .Name = BODY_FONT
        .Size = BODY_SIZE
        .Bold = IIf(isBold, msoTrue, msoFalse)
    End With
    cellShape.Fill.ForeColor.RGB = RGB(255, 255, 255)
End Sub

' =========================
' TOPIC BLOCK EXAMPLES (AI evolution, driving, ecommerce)
' =========================
Private Sub AddAIevolutionBlock(ByVal pres As Presentation)
    ' Slide: AI evolution bullets
    AddBulletsSlide pres, "*AI의 진화*", Array( _
        "AI는 20세기 초 자동제어, 로보틱스, OCR, 머신러닝 등 다양한 이름으로 이미 산업 전반에 적용", _
        "전문가 시스템·분류형 AI 중심의 제한적 활용", _
        "Transformer(2017) 이후 대규모 언어모델 기반 도약", _
        "2022년 11월 ChatGPT 공개가 대중 인식의 분기점", _
        "생성형 AI 성능 급상승으로 텍스트·이미지·음성 생성이 실용 단계 진입", _
        "GUI → Prompt 중심 인터페이스로 전환", _
        "단순 생산성 도구가 아니라 사고 확장 장치로 기능" _
    )
    
    ' Slide: AI evolution diagram + comparison + discussion
    Dim sld As Slide
    Set sld = pres.Slides.Add(pres.Slides.Count + 1, ppLayoutBlank)
    AddTitle sld, pres, "*AI의 진화* (도식/비교/토론)"
    
    Dim W As Single, H As Single
    W = pres.PageSetup.SlideWidth
    H = pres.PageSetup.SlideHeight
    
    ' Timeline (simple arrows)
    Dim timeline As Shape
    Set timeline = sld.Shapes.AddShape(msoShapeRoundedRectangle, M_LEFT, 110, W - M_LEFT - M_RIGHT, 70)
    With timeline
        .Fill.ForeColor.RGB = RGB(255, 255, 255)
        .Line.ForeColor.RGB = RGB(200, 200, 200)
        .TextFrame2.TextRange.Text = "1920s 자동제어 → 전문가 시스템 → 머신러닝 → 딥러닝 → Transformer(2017) → ChatGPT(2022) → Agentic AI"
        .TextFrame2.TextRange.Font.Name = BODY_FONT
        .TextFrame2.TextRange.Font.Size = 16
        .TextFrame2.MarginLeft = 12
        .TextFrame2.MarginRight = 12
        .TextFrame2.MarginTop = 10
        .TextFrame2.MarginBottom = 10
    End With
    
    ' Comparison table (2x5 approx)
    Dim tblShape As Shape
    Set tblShape = sld.Shapes.AddTable(3, 2, M_LEFT, 200, (W - M_LEFT - M_RIGHT) * 0.62, 190)
    Dim tbl As Table
    Set tbl = tblShape.Table
    
    tbl.Cell(1, 1).Shape.TextFrame2.TextRange.Text = "2022년 이전"
    tbl.Cell(1, 2).Shape.TextFrame2.TextRange.Text = "2022년 이후"
    StyleHeaderCell tbl.Cell(1, 1).Shape
    StyleHeaderCell tbl.Cell(1, 2).Shape
    
    tbl.Cell(2, 1).Shape.TextFrame2.TextRange.Text = "과업 특화 AI" & vbCrLf & "분류 중심" & vbCrLf & "GUI 인터페이스" & vbCrLf & "자동화 도구"
    tbl.Cell(2, 2).Shape.TextFrame2.TextRange.Text = "범용 AI" & vbCrLf & "생성 중심" & vbCrLf & "프롬프트 인터페이스" & vbCrLf & "사고 보조자"
    StyleBodyCell tbl.Cell(2, 1).Shape
    StyleBodyCell tbl.Cell(2, 2).Shape
    
    tbl.Cell(3, 1).Shape.TextFrame2.TextRange.Text = ""
    tbl.Cell(3, 2).Shape.TextFrame2.TextRange.Text = ""
    tbl.Cell(3, 1).Shape.Fill.ForeColor.RGB = RGB(255, 255, 255)
    tbl.Cell(3, 2).Shape.Fill.ForeColor.RGB = RGB(255, 255, 255)
    
    ' Discussion question orange box
    Dim dq As Shape
    Set dq = sld.Shapes.AddShape(msoShapeRoundedRectangle, M_LEFT + (W - M_LEFT - M_RIGHT) * 0.66, 200, (W - M_LEFT - M_RIGHT) * 0.34, 190)
    With dq
        .Fill.ForeColor.RGB = ORANGE_RGB
        .Line.ForeColor.RGB = ORANGE_RGB
        .TextFrame2.TextRange.Text = "토론 질문" & vbCrLf & "생성형 AI는 점진적 발전인가, 인지 패러다임의 단절인가?"
        With .TextFrame2.TextRange.Font
            .Name = BODY_FONT
            .Size = 18
            .Bold = msoTrue
            .Fill.ForeColor.RGB = RGB(255, 255, 255)
        End With
        .TextFrame2.MarginLeft = 14
        .TextFrame2.MarginRight = 14
        .TextFrame2.MarginTop = 14
        .TextFrame2.MarginBottom = 14
    End With
End Sub

Private Sub AddAutonomousDrivingBlock(ByVal pres As Presentation)
    AddBulletsSlide pres, "*자율주행*", Array( _
        "1920년대 무선 통제 차량 실험", _
        "2004년 DARPA Grand Challenge 전환점", _
        "2009년 Google(현 Waymo) 프로젝트로 민간 투자 급증", _
        "Tesla Autopilot로 소비자 시장 확산", _
        "ADAS 기반 레벨2 상용화", _
        "차량 플랫폼화: 음성비서/예측정비/맞춤 기능", _
        "통신·센서·딥러닝·클라우드 통합 산업" _
    )
End Sub

Private Sub AddEcommerceBlock(ByVal pres As Presentation)
    AddBulletsSlide pres, "*유통/이커머스*", Array( _
        "아마존 협업필터링 추천 시스템(1990s 후반)", _
        "AWS(2006)로 AI 개발 인프라 대중화 기여", _
        "2010s 물류 로봇 대규모 도입", _
        "재고·배송 최적화로 운영 효율 극대화", _
        "상품평 요약 AI(2023)", _
        "생성형 쇼핑 비서 Rufus(2024)", _
        "데이터·추천·물류·생성형 AI 통합 구조로 재편" _
    )
End Sub


Private Sub StyleHeaderCell(ByVal shp As Shape)
    shp.Fill.ForeColor.RGB = RGB(240, 242, 246)
    With shp.TextFrame2.TextRange.Font
        .Name = BODY_FONT
        .Size = 18
        .Bold = msoTrue
    End With
End Sub

Private Sub StyleBodyCell(ByVal shp As Shape)
    shp.Fill.ForeColor.RGB = RGB(255, 255, 255)
    With shp.TextFrame2.TextRange.Font
        .Name = BODY_FONT
        .Size = 16
        .Bold = msoFalse
    End With
End Sub

Private Sub AddHomeAutomationBlock(ByVal pres As Presentation)

    AddBulletsSlide pres, "*스마트 홈 / 가전 (Home Automation / Appliances)*", Array( _
        "초기 프로그래밍 가능 가전제품 (세탁기, HVAC 제어)", _
        "IoT 기기 확산 (2010년대)", _
        "음성 비서: Alexa, Google Assistant", _
        "스마트 홈 통합 플랫폼", _
        "AI 기반 예측 유지보수 (Predictive Maintenance)", _
        "에너지 최적화 시스템", _
        "자동화 → 자율적 적응 (Autonomous Adaptation)" _
    )
    
    AddConceptComparisonSlide pres, _
        "*스마트 홈 전환 (Home Automation Transformation)*", _
        "규칙 기반 자동화 (Rule-based Automation)", _
        "맥락 인지형 AI 시스템 (Context-aware AI)", _
        "스마트 홈은 진정한 지능인가, 아니면 고도화된 제어 논리인가?"
        
End Sub


Private Sub AddOfficeSWBlock(ByVal pres As Presentation)

    AddBulletsSlide pres, "*오피스 소프트웨어 전환 (Office Software Transformation)*", Array( _
        "MS Office 생산성 제품군 (1990년대–)", _
        "클라우드 협업 시대 (Google Docs)", _
        "내장형 AI 문법 교정 기능", _
        "자동 요약 도구 (Auto Summarization)", _
        "Word/Excel/PPT 내 Copilot 통합", _
        "도구 사용 → 인지적 위임 (Cognitive Delegation)" _
    )
    
    AddConceptComparisonSlide pres, _
        "*오피스 소프트웨어 변화 (Office Software Shift)*", _
        "사용자 주도 편집", _
        "AI 보조 초안 작성 (AI-assisted Drafting)", _
        "AI는 인지 부담을 줄이는가, 아니면 전문가의 역량을 약화시키는가?"
        
End Sub


Private Sub AddWorkToolsBlock(ByVal pres As Presentation)

    AddBulletsSlide pres, "*기업 업무 도구 (Business Work Tools)*", Array( _
        "ERP 시스템 (SAP/Oracle)", _
        "CRM 자동화", _
        "로보틱 프로세스 자동화 (RPA)", _
        "데이터 분석 대시보드", _
        "AI 기반 예측 시스템 (Forecasting)", _
        "의사결정 보강 도구 (Decision Augmentation)", _
        "업무 흐름 최적화 → 전략적 증강 (Strategic Augmentation)" _
    )
    
    AddConceptComparisonSlide pres, _
        "*경영 영향 (Management Impact)*", _
        "운영 자동화", _
        "경영 판단의 증강", _
        "AI는 경영 효과성(Effectiveness)을 대체할 수 있는가 (Drucker)?"
        
End Sub


Private Sub AddEducationBlock(ByVal pres As Presentation)

    AddBulletsSlide pres, "*교육 전환 (Education Transformation)*", Array( _
        "이러닝 플랫폼 (LMS 시스템)", _
        "MOOCs 확산", _
        "적응형 학습 알고리즘 (Adaptive Learning)", _
        "AI 튜터링 시스템", _
        "개인 맞춤형 커리큘럼 생성", _
        "평가 자동화", _
        "학습의 인지적 동반자로서의 AI" _
    )
    
    AddConceptComparisonSlide pres, _
        "*교육 패러다임 (Education Paradigm)*", _
        "표준화된 교육과정", _
        "AI 기반 개인화 학습", _
        "AI는 지적 훈련을 약화시키는가, 아니면 심화시키는가?"
        
End Sub


Private Sub AddPublishingBlock(ByVal pres As Presentation)

    AddBulletsSlide pres, "*출판 / 번역 (Publishing / Translation)*", Array( _
        "데스크탑 출판 혁명", _
        "기계 번역 (Google Translate)", _
        "신경망 번역 기술 혁신 (Neural Translation)", _
        "자동 요약 도구", _
        "AI 공동 저작 시스템 (Co-authoring)", _
        "음성-텍스트 통합 (Speech-to-Text)", _
        "저자 개념의 변화" _
    )
    
    AddConceptComparisonSlide pres, _
        "*저자성 문제 (Authorship Question)*", _
        "인간의 독창성", _
        "AI 협업 생성 (Collaborative Generation)", _
        "지적 소유권(Intellectual Ownership)은 무엇으로 정의되는가?"
        
End Sub


Private Sub AddMedicalBlock(ByVal pres As Presentation)

    AddBulletsSlide pres, "*의료 / 헬스케어 (Medical / Healthcare)*", Array( _
        "의료 영상 진단 AI", _
        "신약 개발 가속화", _
        "유전체 패턴 탐지 (Genomic Pattern Detection)", _
        "원격 환자 모니터링", _
        "AI 임상 의사결정 지원", _
        "로봇 수술 시스템", _
        "윤리적 및 규제 리스크" _
    )
    
    AddConceptComparisonSlide pres, _
        "*헬스케어 위험 차원 (Healthcare Risk Dimension)*", _
        "인간 전문가의 판단", _
        "알고리즘 기반 패턴 추론", _
        "생명과 직결된 AI에 어느 수준의 자율성이 허용되는가?"
        
End Sub


Private Sub AddLegalBlock(ByVal pres As Presentation)

    AddBulletsSlide pres, "*법률 전환 (Legal Transformation)*", Array( _
        "전자 증거개시 도구 (E-discovery)", _
        "계약 검토 자동화", _
        "예측 법률 분석 (Predictive Legal Analytics)", _
        "AI 생성 법률 문서 초안", _
        "고위험 AI 규제", _
        "책임 소재 문제", _
        "AI와 민주적 정당성" _
    )
    
    AddConceptComparisonSlide pres, _
        "*법과 AI (Law & AI)*", _
        "규칙 해석", _
        "알고리즘 의사결정 지원", _
        "AI 시대에 법은 자신의 기초를 재정의해야 하는가?"
        
End Sub


Private Sub AddMediaBlock(ByVal pres As Presentation)

    AddBulletsSlide pres, "*미디어 및 창조 산업 (Media & Creative Industry)*", Array( _
        "디지털 콘텐츠 플랫폼", _
        "AI 생성 이미지 및 음악", _
        "딥페이크 위험", _
        "합성 뉴스 생성 (Synthetic News)", _
        "알고리즘 추천 통제", _
        "문화적 획일화 위험", _
        "AI 기반 문화 생산" _
    )
    
    AddConceptComparisonSlide pres, _
        "*창의성의 진정성 (Creative Authenticity)*", _
        "인간의 창의성", _
        "생성적 재조합 (Generative Recombination)", _
        "AI는 창의적인가, 아니면 조합적 계산인가?"
        
End Sub


Private Sub AddKnowledgeWorkerBlock(ByVal pres As Presentation)

    AddBulletsSlide pres, "*지식 노동자 전환 (Knowledge Worker Transformation)*", Array( _
        "정보 희소성 → 정보 과잉", _
        "사유 파트너로서의 AI", _
        "프롬프트 문해력(Prompt Literacy)의 부상", _
        "메타인지(Meta-cognition)의 중요성", _
        "리버럴 아트(Liberal Arts)의 전략적 가치", _
        "인간의 판단 > 알고리즘 산출물", _
        "경쟁력 = 통합적 추론 능력" _
    )
    
    AddConceptComparisonSlide pres, _
        "*인간의 경쟁 우위 (Human Competitive Advantage)*", _
        "실행 능력", _
        "철학적 판단 및 통합 능력", _
        "무엇이 인간 고유의 영역으로 남는가?"
        
End Sub


Private Sub AddIntegrationSlide(ByVal pres As Presentation)

    AddBulletsSlide pres, "*AI 시대 통합 프레임워크 (AI Era Integration Framework)*", Array( _
        "기술 계층 (LLM, Multimodal, Agentic)", _
        "인프라 계층 (Cloud, Energy, Data Centers)", _
        "제도 계층 (Law, Regulation, Governance)", _
        "조직 계층 (Management, Entrepreneurship)", _
        "인지 계층 (Liberal Arts, Philosophy)", _
        "윤리 계층 (Human Dignity, Responsibility)", _
        "전략적 종합(Synthesis) 필요" _
    )
    
End Sub


Private Sub AddConceptComparisonSlide(ByVal pres As Presentation, _
                                      ByVal titleText As String, _
                                      ByVal leftConcept As String, _
                                      ByVal rightConcept As String, _
                                      ByVal discussion As String)

    Dim sld As Slide
    Set sld = pres.Slides.Add(pres.Slides.Count + 1, ppLayoutBlank)
    AddTitle sld, pres, titleText
    
    Dim W As Single, H As Single
    W = pres.PageSetup.SlideWidth
    H = pres.PageSetup.SlideHeight
    
    Dim tblShape As Shape
    Set tblShape = sld.Shapes.AddTable(2, 2, 40, 140, W * 0.6, 160)
    
    tblShape.Table.Cell(1, 1).Shape.TextFrame2.TextRange.Text = leftConcept
    tblShape.Table.Cell(1, 2).Shape.TextFrame2.TextRange.Text = rightConcept
    
    StyleHeaderCell tblShape.Table.Cell(1, 1).Shape
    StyleHeaderCell tblShape.Table.Cell(1, 2).Shape
    
    Dim dq As Shape
    Set dq = sld.Shapes.AddShape(msoShapeRoundedRectangle, W * 0.65, 140, W * 0.3, 160)
    With dq
        .Fill.ForeColor.RGB = ORANGE_RGB
        .Line.ForeColor.RGB = ORANGE_RGB
        .TextFrame2.TextRange.Text = "Discussion" & vbCrLf & discussion
        With .TextFrame2.TextRange.Font
            .Name = BODY_FONT
            .Size = 18
            .Bold = msoTrue
            .Fill.ForeColor.RGB = RGB(255, 255, 255)
        End With
        .TextFrame2.MarginLeft = 12
        .TextFrame2.MarginRight = 12
        .TextFrame2.MarginTop = 12
        .TextFrame2.MarginBottom = 12
    End With
    
End Sub
```
