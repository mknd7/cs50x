SELECT DISTINCT name FROM people
JOIN stars ON people.id=person_id
JOIN movies ON stars.movie_id=movies.id
WHERE movies.id IN
(
	SELECT movie_id FROM stars
	WHERE person_id IN
	(
		SELECT id FROM people
		WHERE name="Kevin Bacon" AND birth=1958
	)
) AND name!="Kevin Bacon";