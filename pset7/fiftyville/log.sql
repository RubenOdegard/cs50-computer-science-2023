-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find crime scene report from the relevant day of the theft.
SELECT description FROM crime_scene_reports
WHERE day = 28 AND month = 7
AND street = "Humphrey Street";
    -- theft happened at 10:15 am

SELECT name, transcript
FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28
AND transcript LIKE '%bakery%'
ORDER BY name;
    -- Witnesses: Eugene, Raymond, Ruth.

-- check the clue about withdrawing money from Leggett Street
SELECT account_number, amount
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- match bank account numbers against the transactions from the ATM
SELECT name, atm_transactions.amount
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw';
    -- suspect list: Bruce, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista.

-- get information about the airport mentioned by witnesses.
SELECT *
FROM airports
WHERE city = 'Fiftyville';

-- finding fligths out of Fiftyvlle on the day after the theft
SELECT flights.id, full_name, city, flights.hour, flights.minute
FROM airports
JOIN flights
ON airports.id = flights.destination_airport_id
WHERE flights.origin_airport_id =
    (SELECT id FROM airports WHERE city = 'Fiftyville')
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29
ORDER BY flights.hour, flights.minute;
-- first flight leaves at 08:20 to New York City to LaGuardia Airport - Flight ID 36.

-- find people on the fligth
SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
FROM people
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON passengers.flight_id = flights.id
WHERE flights.year = 2021
AND flights.month = 7
AND flights.day = 29
AND flights.hour = 8
AND flights.minute = 20
ORDER BY people.name;
    -- current on-flight list: Bruce, Doris, Edward, Kelsey, Kenny. Luca, Sofia, Taylor.
    -- duplicates from previous suspect list: Bruce, Kenny, Luca, Taylor

-- find name of the persons who made calls less than a minute (by witness description)
SELECT name, phone_calls.duration
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60
ORDER BY phone_calls.duration;
    -- callers : Kelsey, Carina, Taylor, Bruce, Diana, Keylsey, Sofia, Banista, Kenny, Kathryn.
    -- duplicates from previous suspect list: Bruce, Taylor

-- find name of the persons who could have recieved the call
SELECT name, phone_calls.duration
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.receiver
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60
ORDER BY phone_calls.duration;
    -- call receivers: Larry, Jacqueline, James, Robin, Philip, Melissa, Jack, Anna, Doris, Luca.


SELECT name, bakery_security_logs.hour, bakery_security_logs.minute
FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.activity = 'exit'
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15 AND bakery_security_logs.minute <= 25 -- theft happened at 10:15, thief drove away 10 minutes after
ORDER BY bakery_security_logs.minute;
    -- Suspects from bakery logs: Venassa, Bruce, Barry, Luca, Sofia, Iman, Diana, Kelsey
    -- duplicates from previous suspect list: Bruce

    -- Bruce has to be the thief, as he is present in ATM logs, Flight logs, Bakery logs and made a phone call.
    -- The first flight out of Fiftyville goes to New York City.
    -- Bruce's accomplice has to be the reciver of his call.

-- finding Bruces call and the reciver phone number.
SELECT name, caller, receiver
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60
ORDER BY phone_calls.duration;
    -- Bruce called the number (375) 555-8161

-- finding the name of the receiver
SELECT DISTINCT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.receiver
WHERE phone_calls.receiver = "(375) 555-8161";
    -- Robin is on the other end of the call with Bruce.

-- Recap
-- Bruce is the suspect.
-- The landing airport is New York Airport.
-- Robin is his accomplice.
