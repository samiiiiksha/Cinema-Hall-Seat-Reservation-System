# Cinema Hall Seat Reservation System in C

## Objective

To build a cinema hall seat reservation system, allowing users to view seat availability, book seats, cancel bookings, search reservations by customer name, track customer "loyalty" status based on the no. of premium seats they've booked, and view booking statistics, while allowing an admin to manage the list of movies being shown.

### Team Members
- Samiksha Negi
- Farha Naz
- Jyoti Kumari

## Problem Statement

Develop a program that:
- Displays the current seat availability for a selected movie in the cinema hall.
- Allows users to book one or more seats by entering the row letter and seat number, along with the customer's name.
- Prevents booking of already reserved seats and rejects invalid seat input.
- Allows cancellation of an existing booking.
- Searches bookings using the customer's name.
- Displays a booking summary including total seats, booked seats, available seats, and total revenue, for a single movie or across all movies.
- Assigns different ticket prices for Premium (front row) and Regular seats.
- Tracks how many premium seats each customer has booked and assigns a loyalty tier (Bronze, Silver, Gold, Platinum).
- Allows an admin, protected by a username and password, to add movies, remove movies, and view booking summaries.
- Keeps the list of movies sorted alphabetically and prevents duplicate movie titles from being added.

## Algorithm

1. Initialize a starting list of movies, each with all seats set as available.
2. Display the main menu with the option to log in as a User, log in as an Admin, or exit.
3. If the user logs in as a User:
   - Accept and validate the customer's name.
   - Display the User menu with available operations.
   - If View Seat Map is selected:
     - Select a movie from the list.
     - Display the seating layout, showing which seats are booked and which are available, along with Premium/Regular pricing.
   - If Book Seat(s) is selected:
     - Select a movie from the list.
     - Repeatedly accept a row letter and seat number, validate the seat, and check whether it is already booked.
     - Collect the chosen seats, show a confirmation with the total price, and only then reserve the seats and store the customer's name.
     - If a premium seat was booked, update the customer's loyalty record.
   - If Cancel a Booking is selected:
     - Select a movie, accept the row letter and seat number, validate the seat, check whether it is booked, then cancel the booking and clear the customer name.
   - If Search My Bookings is selected:
     - Select a movie and search all its booked seats for the customer's name, displaying matches.
   - If Check Loyalty Status is selected:
     - Look up the customer's premium booking count and display their current loyalty tier.
4. If the user logs in as an Admin:
   - Validate the admin username and password.
   - Display the Admin menu with available operations.
   - If Add Movie is selected: accept a new title, reject it if it already exists, and insert it into the sorted movie list.
   - If Remove Movie is selected: select a movie from the list and remove it.
   - If View Summary is selected: count booked and available seats and calculate total revenue for one movie or for all movies combined.
5. Repeat the relevant menu until the user chooses to go back or exit.

## Learning Outcome

This program helped in understanding the use of 2D and 3D arrays, structures, dynamic memory allocation, linked lists, hash tables, sorting (merge sort) and searching (binary search) algorithms, string handling, functions, input validation, and implementing a more realistic multi-movie reservation system with admin controls and a customer loyalty feature in C.
