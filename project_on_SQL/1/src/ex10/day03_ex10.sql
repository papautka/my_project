INSERT INTO person_order VALUES ((SELECT MAX(person_order.id) + 1 FROM person_order),
                                  (SELECT p.id FROM person p WHERE p.name = 'Denis'),
                                  (SELECT m.id FROM menu m
                                                WHERE  m.pizza_name = 'sicilian pizza'), '20220224');

INSERT INTO person_order VALUES ((SELECT MAX(person_order.id) + 1 FROM person_order),
                                  (SELECT p.id FROM person p WHERE p.name = 'Irina'),
                                  (SELECT m.id FROM menu m
                                                WHERE  m.pizza_name = 'sicilian pizza'), '20220224');