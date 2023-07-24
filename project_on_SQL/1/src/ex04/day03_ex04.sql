
WITH MAN( pizzeria_man, count_man) AS (
    SELECT p3.name AS pizzeria_man, COUNT(*) AS count_man
    FROM person_order po
    INNER JOIN person p ON po.person_id = p.id
    INNER JOIN menu m on po.menu_id = m.id
    INNER JOIN pizzeria p3 on m.pizzeria_id = p3.id
    WHERE p.gender = 'male'
    GROUP BY p3.name
), WOMAN(pizzeria_woman, count_woman) AS (
    SELECT p3.name AS pizzeria_woman, COUNT(*) AS count_woman
    FROM person_order po
    INNER JOIN person p ON po.person_id = p.id
    INNER JOIN menu m on po.menu_id = m.id
    INNER JOIN pizzeria p3 on m.pizzeria_id = p3.id
    WHERE p.gender = 'female'
    GROUP BY p3.name
)

SELECT pizzeria_woman AS pizzeria_name FROM WOMAN
FULL JOIN MAN on pizzeria_man = pizzeria_woman
WHERE NOT(pizzeria_man IS NOT NULL and  pizzeria_woman IS NOT NULL)