# Setting up SDL with Mingw

For sad windows users :(

Keep in mind that these instructions (at least for SDL) are specific to the makefile we are using

## Getting Mingw

1. Go [here](https://osdn.net/projects/mingw/releases/).
	* Download the [mingw setup .exe](https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/)
2. Install to `C:\MinGW` (should be default)
3. MinGW will open a GUI to download specific packages. We want:
	* g++
	* make (mingw32-make)
	* gnu
	* if you arent sure, get all packages with these keywords, or anything related to c++
4. Mark the desired packages for installation and apply changes
5. Finally, add mingw to your path:
	* open `Control Panel`
	* click `System`
	* click `Advanced System Settings`
	* click `Environment Variables`
	* edit `Path`
	* add `C:\MinGW\bin`

MinGW should be good to go! Now for SDL...

## Getting SDL

1. Create the folder `C:\mingwdev`
2. Get the mingw development library from [here](http://libsdl.org/download-2.0.php)
	* [direct link](http://libsdl.org/release/SDL2-devel-2.0.8-mingw.tar.gz) to the correct one
3. Extract and open to find 2 directories
	* Use your best judgement based on your machine
	* If you really don't know, just use `i686-w64-mingw32`
	* idk how much it matters, but remember which one you used
4. In this directory, you will see the folders `bin`, `include`, and `lib`
	* copy `lib` and `include` to `C:\mingwdev` that was created in step 1
5. Now go back and open the `bin` folder
	* should be 2 files, `SDL2.dll` and `sdl-config`
	* copy them both
	* navigate to `C:\Windows\wow64` or whatever its called.
	* paste the files here

## SDL Extension Libraries

1. Download the library
	* Make sure you get the mingw development library
	* for example, sdl_image is [here](https://www.libsdl.org/projects/SDL_image/)
		* Scroll down to development libraries
		* get the one for mingw ([direct link](https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.3-mingw.tar.gz))
	* Same deal for SDL_mixer and SDL_ttf
2. Extract and open
	* open the folder for your machine's architecture
3. Copy the **contents** of `include` and `lib` to `C:\mingwdev\include` and `C:\mingwdev\lib`, respectfully
4. Copy the **contents** of `bin` to `C:\Windows\wow64` or whatever its called.

You should now be able to compile with `mingw32-make` from the `Bandcamp` directory. YAY.