set(RENDER_MODEL_RESOURCES
    win_script.sh
    image_encrypt
    win0.jpg
    )

foreach (res ${RENDER_MODEL_RESOURCES})
	configure_file(${res} ${res} COPYONLY)
endforeach()

