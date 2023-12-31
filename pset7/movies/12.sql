SELECT DISTINCT m.title
FROM movies AS m
JOIN stars AS s_bc ON m.id = s_bc.movie_id
JOIN people AS p_bc ON s_bc.person_id = p_bc.id AND p_bc.name = 'Bradley Cooper'
JOIN stars AS s_jl ON m.id = s_jl.movie_id
JOIN people AS p_jl ON s_jl.person_id = p_jl.id AND p_jl.name = 'Jennifer Lawrence';
