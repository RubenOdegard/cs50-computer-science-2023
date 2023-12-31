SELECT AVG(energy) AS average_enery_from_drake_songs from songs JOIN artists ON songs.artist_id = artists.id WHERE artists.name = "Drake";
