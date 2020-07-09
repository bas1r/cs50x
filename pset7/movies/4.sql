SELECT COUNT(title) "Number of movies with a 10.0 rating" FROM movies WHERE id IN (SELECT movie_id FROM ratings WHERE rating = 10.0); 
