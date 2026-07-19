# Cinema Hall Seat Reservation System in C

## Objective

To build a C program that simulates a cinema hall seat reservation system, allowing users to view seat availability, book seats, cancel bookings, search reservations by customer name, and view booking statistics.

### Team Members
- Samiksha Negi
- Farha Naz
- Jyoti Kumari

## Problem Statement

Develop a program that:
- Displays the current seat availability in the cinema hall.
- Allows users to book a seat by entering the seat number and customer name.
- Prevents booking of already reserved seats.
- Allows cancellation of an existing booking.
- Searches bookings using the customer's name.
- Displays a booking summary including total seats, booked seats, available seats, and total revenue.
- Assigns different ticket prices for Premium and Regular seats.

## Algorithm

1. Initialize all seats as available.
2. Display the main menu with available operations.
3. If the user selects View Seat Availability:
   - Display the seating layout.
   - Show available and booked seats.
4. If the user selects Book a Seat:
   - Accept the row letter and seat number.
   - Validate the seat.
   - Check whether the seat is already booked.
   - Accept the customer's name.
   - Reserve the seat and store the customer name.
5. If the user selects Cancel a Booking:
   - Accept the row letter and seat number.
   - Validate the seat.
   - Check whether the seat is booked.
   - Cancel the booking and remove the customer name.
6. If the user selects Search Booking:
   - Accept the customer name.
   - Search all booked seats.
   - Display the seat number if found.
7. If the user selects View Booking Summary:
   - Count booked and available seats.
   - Calculate the total revenue based on seat prices.
   - Display the booking statistics.
8. Repeat the menu until the user chooses Exit.

## Learning Outcome

This program helped in understanding the use of two-dimensional arrays, string handling, functions, menu-driven programming, input validation, searching, data management, and implementing a simple real-world reservation system using C.