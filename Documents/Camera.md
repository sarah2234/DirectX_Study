# **Camera**
<img src="https://t1.daumcdn.net/cfile/tistory/9985314B5E9D4DBF2A"><br>
* 카메라의 위치 설정
* 카메라가 바라볼 위치(초점) 설정
* 카메라의 기울기 설정 (radian 단위의 pitch, roll, yaw)

----------------------------------------

## **1. Rotation Matrix 만들기**
```
    D3DXMatrixRotationYawPitchRoll(
        &D3DXMATRIX *pOut, // 회전 행렬 저장
        float yaw,
        float pitch,
        float roll);
```
*MSDN에는 D3DX 라이브러리 대신 DirectXMath 라이브러리를 사용하라고 되어있음. DirectXMath를 사용하면 D3DXMatrixRotationYawPitchRoll 대신 XMMatrixRotationRollPitchYaw 함수 호출*

----------------------------------------

## **2. 초점 맞추기**
```
    D3DXVec3TransformCoord( // 위치 벡터(x, y, z, 1)와 4x4 행렬을 곱한 값의 벡터를 구하는 함수
        D3DXVECTOR3 *pOut, // 벡터 저장
        const D3DXVECTOR3 *pV, // 위치 벡터
        const D3DXMATRIX *pM); // 곱할 행렬
```
해당 함수로 각각 카메라의 초점과 카메라의 법선 벡터(?)를 회전 행렬과 곱한다.
```
    D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
```

## **3. 뷰 행렬 만들기**
```
    D3DXMatrixLookAtLH( // 왼손 좌표계(OpenGL과 반대) 뷰 행렬 만들기
        D3DXMATRIX* pOut, // 뷰 행렬 저장
        const D3DXMATRIX* pEye, // 카메라의 위치
        const D3DXMATRIX* pAt, // 카메라의 초점
        const D3DXMATRIX* pUp); // 카메라의 법선 벡터
```