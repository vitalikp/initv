# check program and library cmake file

# check xgettext
find_program(XGETTEXT xgettext)
if (NOT XGETTEXT)
	message(FATAL_ERROR "*** xgettext not found! ***")
else()
	message("-- Found xgettext")
endif()

# check msgmerge
find_program(MSGMERGE msgmerge)
if (NOT MSGMERGE)
	message(FATAL_ERROR "*** msgmerge not found! ***")
else()
	message("-- Found msgmerge")
endif()

# check msgfmt
find_program(MSGFMT msgfmt)
if (NOT MSGFMT)
	message(FATAL_ERROR "*** msgfmt not found! ***")
else()
	message("-- Found msgfmt")
endif()

# check NLS option
option(NLS_ENABLE "Disable Native Language Support" ON)
if (${NLS_ENABLE})
	set(ENABLE_NLS 1)
	set(LOCALEDIR ${datadir}/locale)
endif()

# check SELinux library
option(SELINUX_ENABLE "Disable optional SELINUX support" ON)
if (${SELINUX_ENABLE})
	pkg_check_modules(SELINUX REQUIRED libselinux)
	set(HAVE_SELINUX 1)
endif()