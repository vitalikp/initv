# initv cmake file


include_directories(.)

# initv error
include_directories(error)
add_library(initv_error_obj STATIC
	error/errlist.c
	error/err.c
	error/err.h
)

# initv basic
include_directories(basic)
add_library(initv_basic_obj STATIC
	basic/log.c
	basic/log.h
)
target_link_libraries(initv_basic_obj initv_error_obj)

# initv conf
include_directories(conf)
add_library(initv_conf_obj STATIC
	conf/conf.c
	conf/conf.h
	conf/loc.h
	conf/vcon.h
	conf/os.h
)

# initv core
include_directories(core)
add_library(initv_core_obj STATIC
	core/init.h
	core/mount.h
	core/locale.c
	core/vconsole.c
	core/mount/mount.c
	module/welcome.c
	module/signal.c
	module/hostname.c
	module/mount.c
	module/mac.c
	module/mac.h
)
target_link_libraries(initv_core_obj initv_basic_obj initv_conf_obj)
target_link_libraries(initv_core_obj ${SELINUX_LIBRARIES})

# initv
add_executable(initv
	initv.c
)
target_link_libraries(initv initv_core_obj)
install(TARGETS initv DESTINATION ${sbindir})