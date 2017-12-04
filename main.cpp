#include "frame.h"
#include "image.h"
#include "rectangle.h"
#include <fstream>

typedef unsigned char byte;

const double frames_per_second = 30;
const int duration_in_seconds = 3;

Frame drawFrame(720, 480);

int main(int argc, char * argv[]) {

    const char * cmd =
            "ffmpeg              "
                    "-y                  "
                    "-hide_banner        "
                    "-f rawvideo         "
                    "-pixel_format rgb24 "
                    "-video_size 720x480 "
                    "-r 60               "
                    "-i -                "
                    "-pix_fmt yuv420p    "
                    "-vcodec mpeg4       "
                    "-an                 "
                    "-q:v 5              "
                    "output.mp4          ";

    FILE * pipe = popen(cmd, "w");
    if (pipe == nullptr) {
        std::cout << "error: " << strerror(errno) << std::endl;
        return 1;
    }

    std::vector<Rectangle>rect;

    Rectangle r1 (45, 45, 150, 50, 0x00, 0x00, 0xff);
    r1.setSpeed(100, 20);
    Rectangle r2(45, 45, 200, 55, 0x00, 0x00, 0xff);
    r2.setSpeed(40, 150);
    Rectangle r3(45, 45, 5, 150, 0x00, 0x00, 0xff);
    r3.setSpeed(50, 120);
    Rectangle r4(45, 45, 30, 5, 0x00, 0x00, 0xff);
    r4.setSpeed(100, 80);

    rect.push_back(r1);
    rect.push_back(r2);
    rect.push_back(r3);
    rect.push_back(r4);

    Image img1;
    Image img2;
    Image img3;
    img1.getX(0.0);
    img1.getY(0.0);
    img2.getX(100.0);
    img2.getY(155.0);

    img1.setSpeed(100, 0);
    img2.setSpeed(100, 0);


    img1.load("ducky.bmp", 150, 150);
    img2.load("Patrick.jpg", 150, 150);

    int num_frames = duration_in_seconds * frames_per_second;
    for (int i = 0; i < num_frames; ++i) {
        double dt = 1.0 / frames_per_second;
        drawFrame.clear();
        for (auto &j : rect) {
            j.draw();
            j.update(dt);
        }

        img1.draw();
        img2.draw();
        img1.update(dt);
        img2.update(dt);

        drawFrame.write(pipe);
    }

    fflush(pipe);
    pclose(pipe);

    std::cout << "num_frames: " << num_frames << std::endl;
    std::cout << "Done." << std::endl;

    return 0;
}