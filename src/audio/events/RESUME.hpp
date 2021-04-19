/**
 * @file
 * @author		__AUTHOR_NAME__ <mail@host.com>
 * @copyright	2021 __COMPANY_LTD__
 * @license		<a href="https://opensource.org/licenses/MIT">MIT License</a>
 */

/**
 * The Audio Resume Event.
 *
 * This event is dispatched by the AudioManager when a sound is resumed from a
 * paused state.
 *
 * ```cpp
 * var ambiance = audio.add("key");
 * audio.on(ambiance, "resume", listener);
 * audio.play(ambiance);
 * audio.pause(ambiance);
 * audio.resume(ambiance);
 * ```
 *
 * @since 0.0.0
 */
#define ZEN_AUDIO_EVENTS_RESUME "resume"
