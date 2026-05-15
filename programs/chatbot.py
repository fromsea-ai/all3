"""
Movie Ticket Booking Chatbot
"""

import re

# Movie
movies = {
    'Interstellar': {
        'Morning': '10:00 AM',
        'Afternoon': '2:00 PM',
        'Evening': '6:00 PM'
    },
    'The Dark Knight': {
        'Morning': '11:00 AM',
        'Afternoon': '3:00 PM',
        'Evening': '7:00 PM'
    },
    'Dune': {
        'Morning': '9:30 AM',
        'Afternoon': '1:30 PM',
        'Evening': '5:30 PM'
    }
}

# Pricing
pricing = {
    'Morning': 120,
    'Afternoon': 150,
    'Evening': 200
}


def greet():
    print("\nWelcome to MovieBot!")
    print("Type 'movies' to see available movies.")
    print("Type 'book' to book tickets.")
    print("Type 'exit' to quit.\n")


def show_movies():
    print("\nCurrently Playing Movies:")
    for movie in movies:
        print(f"- {movie}")
    print()


def show_showtimes(movie):
    print(f"\nShowtimes for {movie}:")
    for time_of_day, timing in movies[movie].items():
        print(f"{time_of_day}: {timing} (Rs. {pricing[time_of_day]})")
    print()


def book_tickets():
    show_movies()

    movie_input = input("Enter the movie name: ").strip().lower()
    movie = None

    for m in movies:
        if m.lower() == movie_input:
            movie = m
            break

    if movie is None:
        print("Sorry, that movie is not available.")
        return

    show_showtimes(movie)

    showtime_choice = input("Choose showtime (Morning/Afternoon/Evening): ").strip().title()
    if showtime_choice not in movies[movie]:
        print("Invalid showtime selected.")
        return

    try:
        tickets = int(input("How many tickets do you need? "))
        if tickets <= 0:
            raise ValueError
    except ValueError:
        print("Please enter a valid number of tickets.")
        return

    price_per_ticket = pricing[showtime_choice]
    total_bill = tickets * price_per_ticket

    print("\nBooking Confirmed!")
    print(f"Movie: {movie}")
    print(f"Showtime: {showtime_choice} - {movies[movie][showtime_choice]}")
    print(f"Tickets: {tickets}")
    print(f"Total Amount: Rs. {total_bill}")
    print("Enjoy your movie!\n")


def main():
    greet()

    while True:
        user_input = input("You: ").strip().lower()

        if user_input in ['hi', 'hello', 'hey']:
            print("MovieBot: Hello! Ready to watch a movie?")

        elif user_input == 'movies':
            show_movies()

        elif user_input == 'book':
            book_tickets()

        elif user_input in ['exit', 'bye', 'goodbye']:
            print("MovieBot: Thank you for visiting! Have a great day!")
            break

        else:
            print("MovieBot: I didn't understand that. Try 'movies' or 'book'.")


if __name__ == "__main__":
    main()