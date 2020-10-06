SELECT t1.title FROM
(
	SELECT title FROM movies
	JOIN stars ON movies.id=stars.movie_id
	JOIN people ON stars.person_id=people.id
	WHERE people.name="Johnny Depp"
) t1
INNER JOIN
(
	SELECT title FROM movies
	JOIN stars ON movies.id=stars.movie_id
	JOIN people ON stars.person_id=people.id
	WHERE people.name="Helena Bonham Carter"
) t2
ON t1.title=t2.title;