///
/// # Game State Recorder
///
/// Track game state and input from tick to tick over time.
////////////////////////////////////////////////////////////////////////////////

///
/// # GSR Setup & Shut down
///
#ifndef DECLARED_GAME_STATE_RECORDER

/// Recording of a single ticks starting state (and soon also input).
typedef struct gsr_tick_ {
		uint32_t tick_nr;
		void *state;
		void *input;
} gsr_tick_t;

/// Full recording of states.
// Uses a round robin data structure so that there's always somewhere
// place to put the next frame (at the expense of the oldest one).
typedef struct gst_vhs_t {
	uint32_t next_tick_nr;
	uint32_t capacity;
	gsr_tick_t ticks[];
} gsr_vhs_t;

size_t gsr_requireed_size( uint32_t capacity );
gsr_vhs_t *gsr_init( size_t, void * );
void gsr_term( gsr_vhs_t * );
#elif defined (IMPLEMENT_ME_SENPAI)

size_t gsr_requireed_size( uint32_t capacity ) {
	return sizeof(gsr_vhs_t) + capacity * sizeof( gsr_tick_t );
}


gsr_vhs_t *gsr_init( size_t size, void *mem ) {
	assert( mem );
	
	gsr_vhs_t *recorder = mem;

	recorder->next_tick_nr = 0;
	recorder->capacity =
		( size - sizeof( gsr_vhs_t ) ) / sizeof( gsr_tick_t );

	memset( recorder->ticks, 0, size - sizeof( gsr_vhs_t ) );

	return recorder;
}


void gsr_term( gsr_vhs_t * gsr ) {
	assert( gsr );

	// Free all states
	for ( gsr_tick_t const *tick = &gsr->ticks[0];
		tick < &gsr->ticks[gsr->capacity]; tick++ ) {
		free( tick->state );
	}
}
#endif


///
/// GSR Status
///
#ifndef DECLARED_GAME_STATE_RECORDER
uint32_t gsr_last_tick( gsr_vhs_t const *gsr );
uint32_t gsr_next_tick( gsr_vhs_t const *gsr );
#elif defined (IMPLEMENT_ME_SENPAI)
uint32_t gsr_last_tick( gsr_vhs_t const *gsr ) {
	assert( gsr );
	return gsr->next_tick_nr - 1;
}

uint32_t gsr_next_tick( gsr_vhs_t const *gsr ) {
	assert( gsr );
	return gsr->next_tick_nr;
}
#endif


///
/// GSR Recording
///
#ifndef DECLARED_GAME_STATE_RECORDER
void gsr_record_tick( size_t, void const *state, gsr_vhs_t *gsr );
#elif defined (IMPLEMENT_ME_SENPAI)
void gsr_record_tick( size_t state_size
	, void const *state, gsr_vhs_t *gsr
	) {
	assert( state );

	// Record ticks in a round robin fashion.
	gsr_tick_t *new_tick = &gsr->ticks[ gsr->next_tick_nr % gsr->capacity ];
	new_tick->tick_nr = gsr->next_tick_nr;
	new_tick->state = realloc( new_tick->state, state_size );
	memcpy( new_tick->state, state, state_size );

	gsr->next_tick_nr++;
}
#endif

// Putting include guard at the end of the file
// since it may be checked more than once. 
#ifndef DECLARED_GAME_STATE_RECORDER
#define DECLARED_GAME_STATE_RECORDER
#endif
