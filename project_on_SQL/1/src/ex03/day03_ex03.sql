WITH MAN(pizzeria_man, count_man) AS (
    SELECT p2.name AS pizzeria_man, COUNT(*) AS count_man
    FROM person_visits pv
    INNER JOIN person p ON pv.person_id = p.id
    INNER JOIN pizzeria p2 ON p2.id = pv.pizzeria_id
    WHERE p.gender = 'male'
    GROUP BY p2.name
), WOMAN(pizzeria_woman, count_woman) AS (
    SELECT p2.name AS pizzeria_woman, COUNT(*) AS count_woman
    FROM person_visits pv
    INNER JOIN person p ON pv.person_id = p.id
    INNER JOIN pizzeria p2 ON p2.id = pv.pizzeria_id
    WHERE p.gender = 'female'
    GROUP BY p2.name
)
SELECT pizzeria_man AS pizzeria_name FROM MAN
JOIN WOMAN on pizzeria_man = pizzeria_woman
WHERE count_man !=  count_woman
ORDER BY pizzeria_man