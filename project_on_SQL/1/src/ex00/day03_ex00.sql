SELECT m.pizza_name AS pizza_name,
       m.price AS price,
       piz.name AS pizzeria_name,
       visit_date
FROM person_visits
JOIN menu m on person_visits.pizzeria_id = m.pizzeria_id
JOIN pizzeria piz on m.pizzeria_id = piz.id
JOIN person p on person_visits.person_id = p.id
WHERE (m.price BETWEEN 800 AND 1000) AND p.name LIKE 'Kate'
ORDER BY pizza_name, price, pizzeria_name
