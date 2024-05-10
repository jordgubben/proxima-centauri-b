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
		size_t state_size;
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
/// GSR Playback controls
///
#ifndef DECLARED_GAME_STATE_RECORDER
bool gsr_step_back( gsr_vhs_t *);
bool gsr_has_tick( uint32_t tick_nr, gsr_vhs_t const *);
uint32_t gsr_last_tick( gsr_vhs_t const *gsr );
uint32_t gsr_next_tick( gsr_vhs_t const *gsr );
#elif defined (IMPLEMENT_ME_SENPAI)

/// If possible step back one tick.
bool gsr_step_back( gsr_vhs_t *gsr ) {
	assert( gsr );
	uint32_t last = gsr_last_tick( gsr );
	if ( !gsr_has_tick( last - 1, gsr ) ) {
		return false;
	}
	gsr->next_tick_nr--;
	return true;
}

/// Is there a anything recorded for the given tick number?
bool gsr_has_tick( uint32_t tick_nr, gsr_vhs_t const *gsr ) {
	assert( gsr );
	return gsr->ticks[ tick_nr % gsr->capacity ].tick_nr == tick_nr;
}

/// Get tick to restore (i.e. last recoded one unless we've stepped around since then).
uint32_t gsr_last_tick( gsr_vhs_t const *gsr ) {
	assert( gsr );
	return gsr->next_tick_nr - 1;
}

/// Get the next tick that will be recorded.
uint32_t gsr_next_tick( gsr_vhs_t const *gsr ) {
	assert( gsr );
	return gsr->next_tick_nr;
}
#endif


///
/// GSR Record & Restore
///
#ifndef DECLARED_GAME_STATE_RECORDER
void gsr_record_tick( size_t, void const *state, gsr_vhs_t *gsr );
bool gsr_restore_last( gsr_vhs_t const *, size_t, void *state );
#elif defined (IMPLEMENT_ME_SENPAI)

/// Record game state for a new tick.
void gsr_record_tick( size_t state_size
	, void const *state, gsr_vhs_t *gsr
	) {
	assert( state );

	// Record ticks in a round robin fashion.
	gsr_tick_t *new_tick = &gsr->ticks[ gsr->next_tick_nr % gsr->capacity ];
	new_tick->tick_nr = gsr->next_tick_nr;
	new_tick->state = realloc( new_tick->state, state_size );
	memcpy( new_tick->state, state, state_size );
	new_tick->state_size = state_size;

	gsr->next_tick_nr++;
}

bool gsr_restore_last( gsr_vhs_t const *gsr, size_t state_size, void *state ) {
	uint32_t tick_nr_to_restore = gsr->next_tick_nr - 1;
	const gsr_tick_t *tick_to_restore = &gsr->ticks[ tick_nr_to_restore % gsr->capacity ];
	if ( tick_to_restore->tick_nr != tick_nr_to_restore || !tick_to_restore->state ) {
		printf( "Error: Invalid tick #%u."
			, tick_nr_to_restore
			);
		return false;
	}

	if ( state_size < tick_to_restore->state_size ) {
		printf( "Error: Insufficient space. State requires %zu bytes, but was only provided %zu bytes."
			, tick_to_restore->state_size, state_size
			);
		return false;
	}

	memcpy( state, tick_to_restore->state, tick_to_restore->state_size );
	return true;
}
#endif

// Putting include guard at the end of the file
// since it may be checked more than once. 
#ifndef DECLARED_GAME_STATE_RECORDER
#define DECLARED_GAME_STATE_RECORDER
#endif
