load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "game",
    srcs = [
        "main.cpp",
    ],
    copts = [
        "-std=c++17",
        "-Wall",
        "-Wformat",
    ],
    defines = [
        "IMGUI_IMPL_OPENGL_LOADER_GL3W",
        "REENTRANT",
    ],
<<<<<<< HEAD
    linkopts = ["-lSDL2 -lGL -ldl -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lzip"],
=======
    linkopts = ["-lSDL2 -lGL -ldl -lSDL2_mixer -lSDL2_ttf"],
>>>>>>> 968cb7366b22835e47b43e7986aed4396649b6d6
    deps = [
        "//imgui:imgui_lib",
        "//source:Sources",
    ],
)
