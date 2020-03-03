#include "eneida.h"
#include "stb_ds.h"
#include "stb_perlin.h"
#define MZ_TINYWIN_IMPLEMENTATION
#include "mz_tinywin.h"
#define MZ_LIBRARY_IMPLEMENTATION
#include "mz_library.h"
#define MZ_D3D12_IMPLEMENTATION
#include "mz_d3d12.h"
#define MZ_GRAPHICS_IMPLEMENTATION
#include "mz_graphics.h"
#define TEST0_IMPLEMENTATION
#include "tests/test0.h"

int _fltused;

void start(void) {
  mztinywin_load_api();
  mzd3d12_load_api();
  mzl_load_api();

  SetProcessDPIAware();

  test_api_t tests[16] = {0};
  test0_load_api(&tests[0]);

  test_api_t *test = &tests[0];

  void *window = mzl_create_window("eneida", 1920, 1080);

  if (window && test->init(test->context, window)) {
    for (;;) {
      MSG message = {0};
      if (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
        DispatchMessage(&message);
        if (message.message == WM_QUIT) {
          break;
        }
      } else {
        f64 frame_time;
        f32 frame_delta_time;
        mzl_update_frame_stats(window, "eneida", &frame_time, &frame_delta_time);
        test->update(test->context, frame_time, frame_delta_time);
      }
    }
    test->deinit(test->context);
  }

  ExitProcess(0);
}
