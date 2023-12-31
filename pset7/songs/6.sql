SELECT songs.name AS songs_by_post_malone from songs JOIN artists ON songs.artist_id = artists.id WHERE artists.name = "Post Malone";
