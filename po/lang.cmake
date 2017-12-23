# lang cmake file

# xgettext flags
set(XGETTEXT_OPT -c --no-location -k_ -kN_ -L C)
set(XGETTEXT_OPT ${XGETTEXT_OPT} -f POTFILES)
set(XGETTEXT_OPT ${XGETTEXT_OPT} --package-name ${PACKAGE_NAME})
set(XGETTEXT_OPT ${XGETTEXT_OPT} --package-version ${VERSION})

file(STRINGS po/LINGUAS LOCALES REGEX ^[a-z])
message("-- Languages ${LOCALES}")
foreach(lang ${LOCALES})
	if (NOT EXISTS ${CMAKE_SOURCE_DIR}/po/${lang}.po)
		# create po file
		execute_process(
		INPUT_FILE ${PACKAGE_NAME}.pot
		OUTPUT_FILE ${lang}.po
		COMMAND ${MSGINIT} -o ${lang}.po -i ${PACKAGE_NAME}.pot --l ${lang} --no-translator
		ERROR_QUIET
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/po)
		message("-- MSGINIT ${lang}.po")
	endif()
endforeach()


# create pot file
add_custom_command(
	OUTPUT ${PACKAGE_NAME}.pot
	COMMAND ${XGETTEXT}
	ARGS -o ${CMAKE_SOURCE_DIR}/po/${PACKAGE_NAME}.pot ${XGETTEXT_OPT}
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/po
	COMMENT "  XGETTEXT ${PACKAGE_NAME}.pot" VERBATIM)


foreach(lang ${LOCALES})
	# update po file
	add_custom_command(
		OUTPUT ${lang}.po
		COMMAND ${MSGMERGE}
		ARGS -q -U ${lang}.po ${PACKAGE_NAME}.pot --lang ${lang} --backup=off
		MAIN_DEPENDENCY ${PACKAGE_NAME}.pot
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/po
		COMMENT "  MSGMERGE ${lang}.po" VERBATIM)
	list(APPEND pofiles ${lang}.po)

	# create mo file
	add_custom_command(
		OUTPUT ${lang}.mo
		COMMAND ${MSGFMT}
		ARGS -o ${lang}.mo ${CMAKE_SOURCE_DIR}/po/${lang}.po
		MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/po/${lang}.po
		COMMENT "  MSGFMT\t${lang}.mo" VERBATIM)
	list(APPEND mofiles ${lang}.mo)

	# install mo file
	install(
		FILES build/${lang}.mo
		DESTINATION ${localedir}/${lang}/LC_MESSAGES
		RENAME ${PACKAGE_NAME}.mo)
endforeach()

add_custom_target(update-po DEPENDS ${pofiles})

add_custom_target(lang ALL DEPENDS ${mofiles})
