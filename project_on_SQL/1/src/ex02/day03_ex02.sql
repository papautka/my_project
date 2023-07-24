SELECT m.pizza_name AS pizza_name,
       m.price AS price,
       piz.name AS pizzeria_name
FROM menu AS m
    JOIN pizzeria piz on m.pizzeria_id = piz.id
    LEFT JOIN person_order po on m.id = po.menu_id
    WHERE po.menu_id IS NULL
    ORDER BY pizza_name, price

