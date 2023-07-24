SELECT  m1.pizza_name as pizza_name,
    p1.name as pizzeria_name_1,
    p2.name as pizzeria_name_2,
    m1.price as price
    FROM menu m1
JOIN menu m2 on m1.pizza_name = m2.pizza_name 
    AND m1.price = m2.price
JOIN pizzeria p1 on m1.pizzeria_id = p1.id
JOIN pizzeria p2 on m2.pizzeria_id = p2.id
WHERE m1.pizzeria_id > m2.pizzeria_id
ORDER BY pizza_name