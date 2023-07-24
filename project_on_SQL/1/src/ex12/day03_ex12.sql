INSERT INTO person_order(id, person_id, menu_id, order_date)
SELECT (generate_series((SELECT MAX(po1.id) + 1 FROM person_order po1),
        (SELECT MAX(po2.id) + MAX(po2.person_id) FROM person_order po2))),
    generate_series((SELECT MIN(p.id) FROM person p),
        ((SELECT MAX(p.id) FROM person p))),
       (SELECT m.id FROM menu m WHERE
        m.pizza_name LIKE 'greek pizza'),
       ('2022-02-25');