
void InitWindow(HINSTANCE hInstance, int ShowWnd);
void InitDirect3D(HINSTANCE hInstance);
void Destroy();

WPARAM Running();
LRESULT CALLBACK WndProc(HWND hWnd,	UINT msg, WPARAM wParam, LPARAM lParam);

///////////////////////////////////////////////////////////////////////////////

void InitScene();
void DestroyScene();
void Update();
void Render();

void CreateBackBuffer();
void DeleteBackBuffer();