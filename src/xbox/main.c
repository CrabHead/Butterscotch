#include "data_win.h"
#include "vm.h"
#include <stdlib.h>
#include "stb_ds.h"
#include <stdbool.h>
#include "runner_gamepad.h"
#include "runner_keyboard.h"
#include "runner.h"
#include "input_recording.h"
#include "debug_overlay.h"
#include "gl_legacy_renderer.h"
#include "loop.h"
#include "noop_audio_system.h"
#include "utils.h"
#include "profiler.h"
#include "gettime.h"

#include <hal/video.h>
#include <nxdk/mount.h>
#include <windows.h>
void glContextInit(int window_width, int window_height);

int main(void) {

    XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);
    glContextInit(640, 480);
    NoopAudioSystem_create();
    
    // Mount E: for saves, D: is mounted automatically by auto mount lib
    BOOL mountRet = nxMountDrive('E', "\\Device\\Harddisk0\\Partition1\\");
    if (!mountRet) {
        logInfo("Failed to mount E: drive!\n");
        return 1;
    }

    CommandLineArgs args = {0};
    args.exitAtFrame = -1;
    args.speedMultiplier = 1.0;
    args.fastForwardSpeed = 0.0;
    args.osType = OS_WINDOWS;
    args.renderer = LEGACY_GL;
    args.dataWinPath = "D:\\data.win";
    args.saveFolder = "E:\\UDATA\\FFFF0002";
    args.loadType = DATAWINLOADTYPE_LOAD_PER_CHUNK;
    args.lazyRooms = true;
    args.lazyTextures = true;
    args.lazyAudio = true;
    args.debug = true;

    int ret = loop(args, NULL);
    freeCommandLineArgs(&args);
    return ret;
}