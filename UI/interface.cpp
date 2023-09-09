#include "utilities.cpp"
#include "NPCs.cpp"

const char g_szClassName[] = "GAME CLASS";

global_variable bool running = true;

global_variable Render_State render_state;

#include "platform.cpp"
#include "builder.cpp"
#include "game.cpp"

Render_State sizer(HWND window, Render_State obj){

    RECT rect;
    GetClientRect(window, &rect);

    obj.width = rect.right - rect.left;
    obj.height = rect.bottom - rect.top;

    int size = obj.width * obj.height * sizeof(unsigned int);

    if(obj.memory) VirtualFree(obj.memory,0 , MEM_RELEASE);
    obj.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RELEASE, PAGE_READWRITE);

    obj.bitmap_info.bmiHeader.biSize = sizeof(obj.bitmap_info.bmiHeader);
    obj.bitmap_info.bmiHeader.biWidth = obj.width;
    obj.bitmap_info.bmiHeader.biHeight = obj.height;
    obj.bitmap_info.bmiHeader.biPlanes = 1;
    obj.bitmap_info.bmiHeader.biBitCount = 32;
    obj.bitmap_info.bmiHeader.biCompression = BI_RGB;

    return obj;


}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

	LRESULT result = 0;

    using std::cout;
    using std::endl;

    switch(msg){
    	case WM_CLOSE:
        case WM_DESTROY: {
            running = false;
        } break;

        case WM_SIZE:
        {

            RECT rect;
            GetClientRect(hwnd, &rect);
            //sizer(hwnd, angel);
            //render_state = sizer(hwnd, render_state);

            render_state.width = rect.right - rect.left;
            render_state.height = rect.bottom - rect.top;

            int size = render_state.width * render_state.height * sizeof(unsigned int);

            if(render_state.memory) VirtualFree(render_state.memory,0 , MEM_RELEASE);

            render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
            render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
            render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
            render_state.bitmap_info.bmiHeader.biPlanes = 1;
            render_state.bitmap_info.bmiHeader.biBitCount = 32;
            render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;


        } break;

    	

    	case WM_COMMAND:
    	{
    		
    	}

    	default : {
			result = DefWindowProc(hwnd, msg, wParam, lParam);
    	}
    }

	return result;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
    
    using namespace std;

    WNDCLASS wc = {};
    HWND hwnd;
    MSG Msg;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.lpszClassName = g_szClassName;

    if(!RegisterClass(&wc)){
        MessageBox(NULL, "Window Registration Failed! wc", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    
    hwnd = CreateWindow(
        wc.lpszClassName,
        "Video Game",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 780,
        0, 0, hInstance, NULL);

    if(hwnd == NULL){
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }


    HDC hdc = GetDC(hwnd);

    Input input = {};

    while(running){
    	//input
    	MSG message;

        for (int i = 0; i < BUTTON_COUNT; i++){
            input.buttons[i].changed = false;
        }

    	while (PeekMessage(&message, hwnd, 0, 0, PM_REMOVE)){

            switch(message.message){
                case WM_KEYUP:
                case WM_KEYDOWN: {
                    u32 vk_code = (u32) message.wParam;
                    bool is_down = ((message.lParam  & (1 << 31)) == 0);

                    switch(vk_code){
                        case VK_UP:{
                            input.buttons[BUTTON_UP].is_down = is_down;
                            input.buttons[BUTTON_UP].changed = true;
                        } break;

                        case VK_DOWN:{
                            input.buttons[BUTTON_DOWN].is_down = is_down;
                            input.buttons[BUTTON_DOWN].changed = true;
                        } break;

                        case VK_LEFT: {
                            input.buttons[BUTTON_LEFT].is_down = is_down;
                            input.buttons[BUTTON_LEFT].changed = true;
                        } break;

                        case VK_RIGHT: {
                            input.buttons[BUTTON_RIGHT].is_down = is_down;
                            input.buttons[BUTTON_RIGHT].changed = true;
                        } break;
                    }
                }
                default: {
                   TranslateMessage(&message);
                    DispatchMessage(&message); 
                }
            }
    		
    	}


        //simulate


        simulate_game(&input);


        //render
        try {
            StretchDIBits(hdc,0,0, render_state.width, render_state.height,0,0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
        }

        catch (const exception& e) {
            
            cerr << "Exception caught: " << e.what() << std::endl;
            return 1;

        }
    }

    return 0;

}