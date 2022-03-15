DirectX 11을 이용한 3D 게임 프로그래밍 입문
===
4장 (p.102)
---

### <b>Direct3D</b>
* 응용 프로그램이 3차원 그래픽 가속 기능을 이용해서 3차원 세계를 렌더링할 수 있게 하는 저수준 API  
* 그래픽 하드웨어를 제어할 수 있는 소프트웨어 인터페이스 제공 => 개발자는 하드웨어의 구체적인 세부사항 고려 X
<br></br>  

### <b>COM(Component Object Model)</b>
* 여러 컴포넌트 객체를 이용해 프로그램을 개발하는 모델
* 프로그래밍 언어 독립성(프로그래밍 언어와 상관없이 객체 사용 가능) + 하위 호환성 제공
* COM 객체 = 인터페이스
* COM 규칙
  - COM 인터페이스는 C++의 new 키워드로 생성하지 않음
  - 인터페이스 사용 후 delete 키워드 대신 해당 인터페이스의 Release 메서드 호출
    + 모든 COM 인터페이스는 IUnknown이라는 COM 인터페이스를 상속받는데, IUnknown이 Release 메서드 제공
    + COM 객체들이 자신만의 고유한 방식으로 메모리를 관리하기 때문
   - COM 인터페이스들은 이름이 대문자 I로 시작
<br></br>  

### <b>텍스처</b>
* 텍스처의 원소: texel (pixel: 색상 정보를 담은 버퍼의 원소)
* n 차원 텍스처 = 자료 원소들의 n차원 배열
* 텍스처에는 색상 정보 외 3차원 벡터 저장 가능
* 텍스처의 각 원소는 다음과 같은 특정 형식(format)으로 구성되고, 텍스처는 해당 형식을 따르는 자료만 담을 수 있다: (DXGI_FORMAT_으로 시작)
  - DXGI_FORMAT_R32G32B32_FLOAT: 32비트 부동소수점 성분 세 개
  - DXGI_FORMAT_R16G16B16A16_UNORM: [0, 1] 구간으로 사상되는 16비트 성분 네 개
  - DXGI_FORMAT_R32G32_UNIT: 32비트 부호 없는 정수 성분 두 개
  - DXGI_FORMAT_R8G8B8A8_UNFORM: [0, 1] 구간으로 사상되는 8비트 부호 없는 성분 네 개
  - DXGI_FORMAT_R8G8B8A8_SNORM: [-1, 1] 구간으로 사상되는 8비트 부호 있는 성분 네 개
  - DXGI_FORMAT_R8G8B8A8_SINT: [-128, 127] 구간으로 사상되는 8비트 부호 있는 성분 네 개 (2^8 / 2)
  - DXGI_FORMAT_R8G8B8A8_UINT: [0, 255] 구간으로 사상되는 8비트 부호 없는 정수 성분 네 개 (2^8)
  - DXGI_FORMAT_R8G8B8A8_TYPELESS: 무형식(typeless) 텍스처 형식. 메모리를 먼저 확보해두고 자료의 구체적인 해석 방식은 나중에 텍스처를 파이프라인에 묶을 때 지정
<br></br>  

### <b>Swap Chain</b>
* Double buffering(front buffer + back buffer)으로 형성됨
* Screen Flickering(화면 깜빡임)
  - 버퍼가 지워지고 그릴 때 그리는 속도가 느려 지워진 버퍼가 화면에 노출됨
* Screen Tearing(화면 찢어짐)
  - 버퍼에 새로운 내용을 덮어 쓸 때 현재 그리는 프레임 데이터와 이전 프레임 데이터가 같이 보여짐
* Screen Flickering과 Screen Tearing을 해결하고자 back buffer(후면 버퍼)와 front buffer(전면 버퍼)를 사용
  - front buffer가 화면에 표시되어 있는 동안 애니메이션의 다음 프레임을 back buffer에 그려놓고, 이후에 front buffer와 back buffer의 역할을 맞바꿔서 애니메이션 재생 => presenting(제시)
  - presenting은 현재 front buffer와 back buffer로의 포인터만 맞바꾸는 것으로 구현
<br></br>

### <b>Depth Buffer</b>
* 각 픽셀의 깊이 정보 저장 (가까운 0.0 ~ 1.0 먼)
* 깊이 버퍼의 원소들과 후면 버퍼의 픽셀들은 1:1로 대응
* Direct3D - 깊이 버퍼링 / z-버퍼링을 통해 한 물체의 픽셀들이 다른 물체보다 앞에 있는지 판정  
* 깊이 버퍼의 자료 형식(각 텍셀이 구성되는 방식):
  - DXGI_FORMAT_D32_FLOAT_S8X24_UNIT: 32비트 부동소수점 깊이 값 + [0, 255] 구간으로 사상되는 8비트 부호 없는 정수 스텐실 값 + padding 용으로 쓰이는 24비트
  - DXGI_FORMAT_D32_FLOAT: 32비트 부동소수점 깊이 값
  - DXGI_FORMAT_D24_UNORM_S8_UINT: [0, 1] 구간으로 사상되는 부호 없는 24비트 깊이 값 + [0, 255] 구간으로 사상되는 8비트 부호 없는 정수 스텐실 값
  - DXGI_FORMAT_D16_UNORM: [0, 1] 구간으로 사상되는 부호 없는 16비트 깊이 값 (<i>32 비트 컴퓨터의 경우 4 바이트, 64 비트 컴퓨터의 경우 8 바이트씩 CPU가 읽는데 16비트의 경우 padding이 없나? CPU가 읽는 게 아닌 건가?</i>)
* 렌더링 과정
  1. 후면 버퍼와 깊이 버퍼 초기화
  2. 후면 버퍼의 특정 픽셀 위치에 기록된 깊이 값과 새로 렌더링되는 픽셀의 깊이 값 비교
  3. 더 작은 값(관찰자에게 가장 가까운 픽셀)을 후면 버퍼와 깊이 버퍼에 저장
<br></br>

### <b>텍스처 자원 뷰</b>
* Direct3D에서 텍스처를 사용하려면 텍스처의 초기화 시점에서 해당 텍스처의 resource view(자원 뷰) 생성 필요
  - 뷰 생성 시점에서 유효성 점검과 매핑을 하므로 binding 시점에서의 형식 점검 최소화
* Bind Flag(결속 플래그)
  - 역할: <span style='background-color: #888000'>resource view를 묶을 두 파이프라인 단계 지정</span>
  - D3D11_BIND_RENDER_TARGET: resource view를 렌더 대상으로 묶음(binding)
  - D3D11_BIND_SHADER_RESOURCE: resource view를 셰이더 자원으로서 묶음
* View
  - 역할
    + Direct3D에게 <span style='background-color: #888000'>resource가 파이프라인의 어떤 단계에 묶일 것인지</span> 알려주기
    + 생성 시점에서 무형식으로 지정한 resource의 구체적인 형식 결정
  - <span style='background-color: #888000'>어떤 자원에 대해 특정 뷰를 생성할 때 bind flag가 지정되어 있어야 함</span>
  - ID3D11RenderTargetView: 렌더 대싱 뷰
  - ID3D11ShaderResourceView: 셰이더 자원 뷰
<br></br>

### <b>다중표본화 이론</b>
* Aliasing(계단 현상): 선을 픽셀들의 배열로 근사할 때 생기는 현상
* Antialiasing
  - Supersampling(초과표본화) / Downsampling(하향표준화)
    1. back buffer, depth buffer를 화면 해상도보다 4배 크게 잡음
    2. 이미지를 화면에 제시할 때 back buffer를 원래 크기의 버퍼로 resolve(환원)
    3. resolve하는 과정에서 4픽셀 블록의 네 색상의 평균을 최종 색상으로 사용   
    => <span style='background-color: #b33000'>픽셀 처리량, 메모리 소비량 ↑
* Multisampling(다중표본화)
  1. 이미지 색상을 픽셀의 중심에서 한 번만 계산
  2. 그 색상과 부분픽셀들의 가시성과 포괄도를 이용해서 최종 색상 결정   
(참고: https://lipcoder.tistory.com/22)