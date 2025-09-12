#!/usr/bin/env python
import os
import sys

app_path = "application"
lib_name = "gdextension"

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(
    CPPPATH=[
        "native/framework/include",
        "native/node/include"
    ]
)
sources = \
    Glob("native/*.cpp") + \
    Glob("native/framework/src/*.cpp") + \
    Glob("native/framework/src/**/*.cpp") + \
    Glob("native/node/src/*.cpp") + \
    Glob("native/node/src/**/*.cpp") + \
    Glob("native/node/src/**/**/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "{}/bin/lib{}.{}.{}.framework/lib{}.{}.{}".format(
            app_path, lib_name, env["platform"], env["target"], lib_name, env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "{}/bin/lib{}.{}.{}.simulator.a".format(
                app_path, lib_name, env["platform"], env["target"]
            ),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "{}/bin/lib{}.{}.{}.a".format(
                app_path, lib_name, env["platform"], env["target"]
            ),
            source=sources,
        )
else:
    library = env.SharedLibrary(
        "{}/bin/lib{}{}{}".format(
            app_path, lib_name, env["suffix"], env["SHLIBSUFFIX"]
        ),
        source=sources,
    )

Default(library)
