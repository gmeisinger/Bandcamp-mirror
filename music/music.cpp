
bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;    
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;    
    }
    
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;    
    }
    
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;    
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "Monitor Music", NULL );
    
    //If everything initialized fine
    return true;
}

bool load_files()
{

	//Load the music
	music = Mix_LoadMUS("beat.wav");
    
	//If there was a problem loading the music
	if( music == NULL )
	{
		return false;    
	}

	//If no problems, continue
	return true;	
}//end load_files

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );
   
    //Free the music
    Mix_FreeMusic( music );
    
    //Close the font
    TTF_CloseFont( font );
    
    //Quit SDL_mixer
    Mix_CloseAudio();
    
    //Quit SDL_ttf
    TTF_Quit();
    
    //Quit SDL
    SDL_Quit();
}
