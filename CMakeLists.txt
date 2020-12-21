set(COMPONENT_SRCS
    api/core/src/vl6180x_api.c
    api/platform/src/vl6180x_i2c.c
    api/platform/src/vl6180x_platform.c
)

set(COMPONENT_ADD_INCLUDEDIRS
    inc
    api/config
    api/core/inc
    api/platform/inc
)

register_component()

target_compile_definitions(${COMPONENT_TARGET}
    PRIVATE USE_I2C_2V8=1
)

target_compile_options(${COMPONENT_TARGET}
    PRIVATE -mlongcalls
)
