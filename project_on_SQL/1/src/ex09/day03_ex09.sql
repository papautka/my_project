INSERT INTO person_visits VALUES ((SELECT MAX(person_visits.id) + 1 FROM person_visits),
                                  (SELECT p.id FROM person p WHERE p.name = 'Denis'),
                                  (SELECT pi.id FROM pizzeria pi
                                                WHERE  pi.name = 'Dominos'), '20220224');

INSERT INTO person_visits VALUES ((SELECT MAX(person_visits.id) + 1 FROM person_visits),
                                  (SELECT p.id FROM person p WHERE p.name = 'Irina'),
                                  (SELECT pi.id FROM pizzeria pi
                                                WHERE  pi.name = 'Dominos'), '20220224');