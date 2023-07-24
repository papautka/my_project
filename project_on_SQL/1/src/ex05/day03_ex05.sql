SELECT DISTINCT 
       p2.name AS pizza_name
FROM person_visits pv
JOIN person p on pv.person_id = p.id
JOIN person_order po on p.id = po.person_id
JOIN pizzeria p2 on pv.pizzeria_id = p2.id
WHERE p.name LIKE 'Andrey' AND visit_date != order_date