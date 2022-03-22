DirectX 11을 이용한 3D 게임 프로그래밍 입문
===
<i>4.1 (p.102)</i>
---

### <b>Direct3D</b>
* 응용 프로그램이 3차원 그래픽 가속 기능을 이용해서 3차원 세계를 렌더링할 수 있게 하는 저수준 API  
* 그래픽 하드웨어를 제어할 수 있는 소프트웨어 인터페이스 제공 => 개발자는 하드웨어의 구체적인 세부사항 고려 X
<br/><br />  

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
<br/><br />

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
<br/><br /> 

### <b>Swap Chain</b>
* Double buffering(front buffer + back buffer)으로 형성됨
* Screen Flickering(화면 깜빡임)
  - 버퍼가 지워지고 그릴 때 그리는 속도가 느려 지워진 버퍼가 화면에 노출됨
* Screen Tearing(화면 찢어짐)
  - 버퍼에 새로운 내용을 덮어 쓸 때 현재 그리는 프레임 데이터와 이전 프레임 데이터가 같이 보여짐
* Screen Flickering과 Screen Tearing을 해결하고자 back buffer(후면 버퍼)와 front buffer(전면 버퍼)를 사용
  - front buffer가 화면에 표시되어 있는 동안 애니메이션의 다음 프레임을 back buffer에 그려놓고, 이후에 front buffer와 back buffer의 역할을 맞바꿔서 애니메이션 재생 => presenting(제시)
  - presenting은 현재 front buffer와 back buffer로의 포인터만 맞바꾸는 것으로 구현
<br/><br />

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
<br/><br />

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
<br/><br />

### <b>Multisampling 이론</b>
* Aliasing(계단 현상): 선을 픽셀들의 배열로 근사할 때 생기는 현상
* Antialiasing
  - Supersampling(초과표본화) / Downsampling(하향표준화)
    1. back buffer, depth buffer를 화면 해상도보다 4배 크게(가로, 세로로 각각 2배씩) 잡음
    2. 4픽셀 블록의 네 색상의 평균을 최종 색상으로 사용
    3. 이미지를 화면에 제시할 때 back buffer를 원래 크기의 버퍼로 resolve(환원)   
    => <span style='background-color: #b33000'>픽셀 처리량, 메모리 소비량 ↑
* Multisampling(다중표본화) (참고: https://lipcoder.tistory.com/22)
  1. back buffer, depth buffer를 화면 해상도보다 4배 크게(가로, 세로로 각각 2배씩) 잡음
  2. 이미지 색상을 픽셀의 중심에서 한 번만 계산
  3. 그 색상과 부분픽셀들의 가시성과 포괄도(부분픽셀을 다각형이 어느 정도 덮고 있는지 나타내는 값)를 이용해서 최종 색상 결정   
    - DXGI_SAMPLE_DESC: 다중표본화를 사용하기 위한 구조체 (DXGI_SWAP_CHAIN_DESC에서 사용)
      + UINT Count: 픽셀당 추출할 표본의 개수 (최대 32)
      + UINT Quality: 품질 수준 지정  
      => 표본 개수가 많을수록, 품질 수준이 높을수록 렌더링 비용 ↑  
      => 다중표본화를 사용하지 않으려면 Count = 1, Quality = 0으로 맞춤
    - CheckMultisampleQualityLevels: 텍스처 형식과 표본 개수의 조합에 대한 품질 수준들의 개수 리턴
      + 참고: https://docs.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11device-checkmultisamplequalitylevels

### <b>Feature Level(기능 수준)</b>
* D3D_FEATURE_LEVEL
* GPU가 지원하는 기능들의 엄격한 집합 정의 (ex: feature level 11을 지원하는 GPU는 반드시 Direct3D 11의 기능 집합 전체를 지원해야 함)
* 응용 프로그램은 feature level 지원 여부를 최신 feature level(D3D 12)에서부터 주어진 응용 프로그램이 허용하는 가장 오래된 feature level까지 체크
* 구형 하드웨어까지 고려하여 응용 프로그램의 사용자층을 최대화할 수 있음
<br><br />
<br><br />

<i>4.1 (p.102)</i>
---
### <b>Direct3D 초기화</b>
(책 기준)
1. D3D11CreateDevice를 이용하여 ID3D11Device 인터페이스와 ID3D11DeviceContext 인터페이스 생성
2. ID3D11Device::CheckMultisampleQualityLevels 메서드를 이용하여 다중표본화를 이용한 안티 앨리어싱 체크
3. DXGI_SWAP_CHAIN_DESC 구조체 생성
4. IDXGISwapChain 인스턴스 생성
5. Swap Chain의 back buffer에 대한 Render Target View 생성
6. depth-stencil buffer와 depth-stencil view 생성
7. Render Target View와 depth-stencil view를 Direct3D가 사용할 수 있도록 렌더링 파이프라인의 출력 병합기 단계에 묶음
8. 뷰포트 설정  
<!---->
<br><br />

(내가 작성한 코드 기준)  
Device.h: <https://github.com/sarah2234/Study_DirectX/blob/main/DirectX11/DirectX11/Device.h>  
Device.c: <https://github.com/sarah2234/Study_DirectX/blob/main/DirectX11/DirectX11/Device.cpp>  
1. DXGI_SWAP_CHAIN_DESC로 사용할 swap chain의 특성 지정
  * BufferCount: 사용할 백 버퍼 개수
  * BufferUsage: 백 버퍼의 용도 (DXGI_USAGE_RENDER_TARGET_OUTPUT)
  * OutputWindow: 결과를 출력할 윈도우
  * Windowed: 창 모드로 생성 여부 (true)
  * SwapEffect: 백 버퍼에서 프론트 버퍼로 가져올 형식
  <br><br />
  swap chain의 버퍼 특성
  * BufferDesc.Format: 출력 형식 지정 (텍스처 형식)
  * BufferDesc.Width: 버퍼의 너비 (코드에서는 뷰포트의 너비만큼 지정)
  * BufferDesc.Height: 버퍼의 높이 (코드에서는 뷰포트의 높이만큼 지정)
  <br><br />
  멀티샘플링(DXGI_SAMPLE_DESC)
  * SampleDesc.Count: 멀티 샘플링 개수
  * SampleDesc.Quality: 품질 레벨

<br><br />
2. D3D11CreateDeviceAndSwapChain: device와 swap chain 동시에 생성  
  *Device.cpp에 적힌 매개변수대로 사용하면 될 것

<br><br />
3. Back Buffer 정보 받아오기
  * swapChain->GetBuffer()  
  *Device.cpp에 적힌 매개변수대로 사용하면 될 것

<br><br />
4. Render Target View 생성
  * resource를 파이프라인에 직접 묶는 대신, resource에 대한 뷰룰 생성하고 그 뷰를 파이프라인 단계에 묶어야 함
  * Direct3D가 버퍼에 그림을 그리려면, 백 버퍼에 대한 Render Target View를 생성 -> 백 버퍼를 파이프라인의 output merger 단계에 묶기
  * D3D11CreateDeviceAndSwapChain에서 생성한 device로 CreateRenderTargetView 호출하여 RTV 생성
  * RTV 만든 후 백 버퍼는 Release

<br><br />
5. depth-stencil buffer 생성
* <i>Device.cpp에 없네??</i>
* D3D11_TEXTURE2D_DESC: 2차원 텍스처를 생성하는 구조체
```
D3D11_TEXTURE2D_DESC depthStencilDesc;
depthStencilDesc.Width = windowWidth; // 텍셀의 너비
depthStencilDesc.Height = windowHeight; // 텍셀의 높이
depthStencilDesc.MipLevels = 1; // 밉맵 수준의 개수
depthStencilDesc.ArraySize = 1; // 택스처 배열의 텍스처 개수
depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
if(멀티샘플링 사용 x)
{
  depthStencilDesc.SampleDesc.Count = 1;
  depthStencilDesc.SampleDesc.Quality = 0;
}
depthStencilDesc.Usage = D3D11_USAGE_DEFAULT; // GPU가 resource를 읽고 씀 (CPU는 불가)
depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // resource를 파이프라인에 묶는 방식 지정
depthStencilDesc.CPUAccessFlags = 0; // CPU 대신 GPU가 depth-stencil buffer에 접근하므로 0으로 지정
dpethStencilDesc.MiscFlags = 0; // 기타 플래그

ID3D11Texture2D* mDepthStencilBuffer; // depth-stencil buffer
ID3D11DepthStencilView* mDepthStencilView; // depth-stencil view를 생성해서 파이프라인에 붙여야 buffer 사용 가능
// 모든 버퍼들은 그에 대한 뷰를 생성해서 파이프라인에 붙여야 사용이 가능하나보다.

device->CreateTexture2D(
  &depthStencilDesc,
  0, // 텍스처에 채울 초기 자료가 없음
  &mDepthStencilBuffer); // buffer 생성

device->CreateDepthStencilView(
  mDepthStencilBuffer,
  0,
  &mDepthStencilView);
```

6. 생성한 view들(back buffer, depth-stencil buffer에 대한 뷰)을 파이프라인의 output merger stage에 묶기
  * deviceContext->OMSetRenderTargets로 RTV와 Depth-Stencil View를 파이프라인에 묶기

7. Viewport 설정
  * D3D11_VIEWPORT 구조체로 뷰포트 설정하고 ID3D11DeviceContext::RSSetViewports 메서드를 이용해서 Direct3D에게 뷰포트를 알려줌