// FIP project.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;

struct Date
{
    int day;
    int month;
    int year;
};
struct GuestInfo
{
    std::string GuestNameFirst;
    std::string GuestNameLast;
    std::string ContactNumber;
    std::string GuestAddress;
};

struct HotelRoom
{
    std::string Type;
    int CostPerNight = 0;
    int RoomID = 0;
    bool Room_status = true;
    double Taxes = 0;
    Date CheckinDate;
    Date CheckoutDate;
    int BookingID = 0;
    GuestInfo guestinfo;
};

bool ValidateCheckinDates(const Date& CheckinDate)
{
    // ensuring that date entered is not alien values that a date cannot be

    if (CheckinDate.day >= 1 && CheckinDate.day <= 31 && CheckinDate.month >= 1 && CheckinDate.month <= 12
        && CheckinDate.year >= 2000 && CheckinDate.year <= 2030)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ValidateCheckoutDates(const Date& CheckoutDate)
{
    // ensuring that date entered is not alien values that a date cannot be

    if (CheckoutDate.day >= 1 && CheckoutDate.day <= 31 && CheckoutDate.month >= 1 && CheckoutDate.month <= 12
        && CheckoutDate.year >= 2000 && CheckoutDate.year <= 2030)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool IsCheckoutDateAfterCheckin(const Date& CheckoutDate, const Date& CheckinDate)
{
    if (CheckoutDate.year < CheckinDate.year)  // comparing years first
    {
        return false;
    }
    else if (CheckoutDate.year == CheckinDate.year)  // same years
    {
        if (CheckoutDate.month < CheckinDate.month)   // so compare months
        {
            return false;
        }
        else if (CheckoutDate.month == CheckinDate.month)  // same months
        {
            if (CheckoutDate.day < CheckinDate.day)   // then compare days
            {
                return false;
            }
        }
    }
    return true;  // will return true value ONLY when check out date is after check in date
}


void OutputCheckinDate(const Date& CheckinDate)
{
    std::cout << "Check-in date: " << CheckinDate.day << "/" << CheckinDate.month << "/" << CheckinDate.year << std::endl;
}

void OutputCheckoutDate(const Date& CheckoutDate)
{
    std::cout << "Check-out date: " << CheckoutDate.day << "/" << CheckoutDate.month << "/" << CheckoutDate.year << std::endl;
}

bool IsRoomIDValid(int RID, int NumRoom)
{
    return (RID >= 1 && RID <= NumRoom);
}

void InitializeRooms(HotelRoom HRoom[], int NumRoom)
{
    for (int j = 0; j < NumRoom; ++j)
    {
        HRoom[j].RoomID = j + 1;
        HRoom[j].Room_status = true;
        HRoom[j].guestinfo.GuestNameFirst = "";
        HRoom[j].guestinfo.GuestNameLast = "";
        HRoom[j].guestinfo.ContactNumber = "";
        HRoom[j].guestinfo.GuestAddress = "";
        HRoom[j].BookingID = -1;
    }
};

void DisplayAvailableRoom(HotelRoom HRoom[], int NumRoom)
{
    std::cout << "These are all the available rooms: " << std::endl;
    std::cout << std::endl;
    std::cout << "Room ID \t Room Type" << std::endl;
    std::cout << std::endl;
    for (int j = 0; j < NumRoom; ++j)
    {
        if (HRoom[j].Room_status)
        {
            std::cout << HRoom[j].RoomID << "\t" << HRoom[j].Type << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        }
    }
}

void DisplayBookedRoom(HotelRoom HRoom[], int NumRoom, const Date& CheckinDate, const Date& CheckoutDate)
{
    for (int j = 0; j < NumRoom; ++j)
    {
        if (!HRoom[j].Room_status)
        {
            std::cout << "These are the booked rooms: " << std::endl;
            std::cout << std::endl;
            std::cout << "Room ID \t Type" << std::endl;
            std::cout << std::endl;
            std::cout << HRoom[j].RoomID << "\t" << HRoom[j].Type << std::endl;
            std::cout << std::endl;
            std::cout << "Details of Guest." << std::endl;
            std::cout << "     -------     " << std::endl;
            std::cout << "Booking ID: " << HRoom[j].BookingID << std::endl;
            std::cout << "Name:" << HRoom[j].guestinfo.GuestNameFirst << " " << HRoom[j].guestinfo.GuestNameLast << std::endl;

            OutputCheckinDate(CheckinDate);  
            OutputCheckoutDate(CheckoutDate);

            std::cout << "Contact number: " << HRoom[j].guestinfo.ContactNumber << std::endl;
            std::cout << "Address: " << HRoom[j].guestinfo.GuestAddress << std::endl;
        }
    }
}

void SearchbyRoomID(HotelRoom HRoom[], int NumRoom, int RID)
{
    std::cout << "Please enter the Room ID - ";
    std::cin >> RID;
    std::cout << std::endl;

    if (!IsRoomIDValid(RID, NumRoom))   // checking if room id is valid first
    {
        std::cout << "Invalid ID! There are only rooms numbered between 1-16! Please enter again." << std::endl;
        std::cout << std::endl;
    }
    else if (IsRoomIDValid(RID, NumRoom))
    {
        std::cout << "Searching for room.." << std::endl;
        std::cout << std::endl;
        for (int j = 0; j < NumRoom; ++j)
        {
            if (HRoom[j].RoomID == RID)
            {
                std::cout << "Room found!" << std::endl;
                std::cout << std::endl;
                std::cout << "Room ID: " << HRoom[j].RoomID << "\t" << HRoom[j].Type << std::endl;
                std::cout << "Status: " << (HRoom[j].Room_status ? "Available" : "Reserved") << std::endl;
                if (!HRoom[j].Room_status)
                {
                    std::cout << "Details of Guest staying in room: " << std::endl;
                    std::cout << "Booking ID: " << HRoom[j].BookingID << std::endl;
                    std::cout << "Name:" << HRoom[j].guestinfo.GuestNameFirst << " " << HRoom[j].guestinfo.GuestNameLast << std::endl;
                    std::cout << "Check-in date: " << HRoom[j].CheckinDate.day << "/" << HRoom[j].CheckinDate.month << "/";
                    std::cout << HRoom[j].CheckinDate.year << std::endl;
                    std::cout << "Check-out date: " << HRoom[j].CheckoutDate.day << "/" << HRoom[j].CheckoutDate.month << "/";
                    std::cout << HRoom[j].CheckoutDate.year << std::endl;
                    std::cout << "Contact number: " << HRoom[j].guestinfo.ContactNumber << std::endl;
                    std::cout << "Address: " << HRoom[j].guestinfo.GuestAddress << std::endl;
                    break;
                }
            }
        }
    }
}

void UpdateRoomDetails(HotelRoom HRoom[], const GuestInfo& GuestDetails,
    int& BookingID, const Date& CheckinDate, const Date& CheckoutDate, int RID)
{
    HRoom[RID - 1].Room_status = false;
    HRoom[RID - 1].BookingID = ++BookingID;
    HRoom[RID - 1].guestinfo = GuestDetails;
    HRoom[RID - 1].CheckinDate = CheckinDate;
    HRoom[RID - 1].CheckoutDate = CheckoutDate;
}

void BookRoom(HotelRoom HRoom[], GuestInfo& GuestDetails, int NumRoom, int& BookingID, Date& CheckinDate, Date& CheckoutDate)
{
    int RID = 0;

    std::cout << "Please enter the Room ID of the room you wish to book - ";
    std::cin >> RID;
    std::cout << std::endl;

    if (IsRoomIDValid(RID, NumRoom))
    {
        std::cout << "Booking room.." << std::endl;
        std::cout << std::endl;
        if (!HRoom[RID - 1].Room_status)
        {
            std::cout << "Room " << RID << " " << "is already booked!" << std::endl;
        }
        else
        {
            std::cout << "Enter details of the guest." << std::endl;
            std::cout << std::endl;
            std::string GuestNameFirst;
            std::string GuestNameLast;
            std::cout << "First name - ";
            std::cin >> GuestDetails.GuestNameFirst;
            std::cout << "Last name - ";
            std::cin >> GuestDetails.GuestNameLast;
            std::string GuestAddress;

            std::cin.ignore();

            std::cout << "Address - ";
            std::getline(std::cin, GuestDetails.GuestAddress);
            std::string Contact_Number;

            do
            {
                std::cout << "Contact Number (It must start with '+94' and only 10 digits long) - ";
                std::cin >> GuestDetails.ContactNumber;

                if (GuestDetails.ContactNumber.length() == 10 && GuestDetails.ContactNumber.substr(0, 3) == "+94")
                {
                    break;
                }
                else
                {
                    std::cout << "Contact number must only be 9 digits long and must follow the +94 code." << std::endl;
                }
            } while (true);

            bool ValidCheckinDate = false;
            do
            {
                std::cout << "Date of check-in (DD/MM/YYYY) - " << std::endl;
                std::cout << "Day - ";
                std::cin >> CheckinDate.day;
                std::cout << "Month - ";
                std::cin >> CheckinDate.month;
                std::cout << "Year - ";
                std::cin >> CheckinDate.year;

                if (!ValidateCheckinDates(CheckinDate))
                {
                    std::cout << "Invalid date entered!" << std::endl;
                    std::cout << std::endl;
                }
                else { ValidCheckinDate = true; }
            } while (!ValidCheckinDate);

            bool ValidCheckoutDate = false;

            do
            {
                std::cout << "Date of check-out (DD/MM/YYYY) - " << std::endl;
                std::cout << "Day - ";
                std::cin >> CheckoutDate.day;
                std::cout << "Month - ";
                std::cin >> CheckoutDate.month;
                std::cout << "Year - ";
                std::cin >> CheckoutDate.year;

                if (!ValidateCheckoutDates(CheckoutDate))
                {
                    std::cout << "Invalid date entered!" << std::endl;
                    std::cout << std::endl;
                }
                else
                {
                        if (!IsCheckoutDateAfterCheckin(CheckoutDate, CheckinDate))
                        {
                            std::cout << "Invalid date entered! Check-out date has to be after check-in date." << std::endl;
                            std::cout << std::endl;
                        } 
                        else
                        {
                            ValidCheckoutDate = true;
                        }
                    
                }
            } while (!ValidCheckoutDate);

            // now we update the details about the room

            UpdateRoomDetails(HRoom, GuestDetails, BookingID, CheckinDate, CheckoutDate, RID);
            std::cout << std::endl;
            std::cout << "Room " << RID << " is booked successfully!" << " Your Booking ID is " << HRoom[RID - 1].BookingID << "." << std::endl;
            HRoom[RID - 1].Room_status = false;
        }
    }
    else if (!IsRoomIDValid(RID, NumRoom))
    {
        std::cout << "Invalid Room ID! There are only rooms numbered between 1-16!" << std::endl;
        return;
    }
}

double CalculateTotalAmount(const HotelRoom& Room, int NumNights)
{
    double TotalAmount = Room.CostPerNight * NumNights;
    // total cost calculated by multiplying duration of stay by cost of room for one night
    double Taxes = 1399.99;
    TotalAmount += Taxes;  // adding taxes
    
    return TotalAmount;
}

void GenerateBill(const HotelRoom& Room, int NumNights, double AddCharges, const GuestInfo& GuestDetails)
{
    std::cout << "Generating bill.." << std::endl;
    std::cout << std::endl;
    double TotalAmount = CalculateTotalAmount(Room, NumNights);   // calling the Calculate function
    TotalAmount += AddCharges;                                    // adding extra charges, if any, to total amount

    // output bill with guest details
    std::cout << "  BILL" << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Booking ID: " << Room.BookingID << std::endl;
    std::cout << "Name: " << GuestDetails.GuestNameFirst << " " << GuestDetails.GuestNameLast << std::endl;
    std::cout << "Total Amount: " << TotalAmount << " " << "LKR" << std::endl;
}

int main()
{
    const int NumRoom = 16;      // iniliazing number of rooms in hotel

    HotelRoom HRoom[NumRoom];   // declaring the HRoom array ; it is an array of Hotel_room structs ; index is NumRoom because that is the amount of rooms in hotel
    // each member represents one hotel room

    HotelRoom Room;               //  represents one single room ; a single instance of Hotel_room struct

    Date CheckinDate{ 1,1,2000 };   // initliazing the check-in date to 1st Janauary, 2000
    Date CheckoutDate{ 1,1,2000 };   // initliazing the check-out date to 1st Janauary, 2000

    GuestInfo GuestDetails;          // declaring variable GuestDetails of the type GuestInfo struct

    // assigning the different types of rooms  ; assumption made that there are 4 room types but different standards (Standard or Deluxe)
    // and whether AC or No AC
    HRoom[0].Type = "AC Standard Single Room";
    HRoom[1].Type = "AC Standard Double Room";
    HRoom[2].Type = "AC Standard Twin Room";
    HRoom[3].Type = "AC Standard Family Room";
    HRoom[4].Type = "AC Deluxe Single Room";
    HRoom[5].Type = "AC Deluxe Double Room";
    HRoom[6].Type = "AC Deluxe Twin Room";
    HRoom[7].Type = "AC Deluxe Family Room";
    HRoom[8].Type = "Non-AC Standard Single Room";
    HRoom[9].Type = "Non-AC Standard Double Room";
    HRoom[10].Type = "Non-AC Standard Twin Room";
    HRoom[11].Type = "Non-AC Standard Family Room";
    HRoom[12].Type = "Non-AC Deluxe Single Room";
    HRoom[13].Type = "Non-AC Deluxe Double Room";
    HRoom[14].Type = "Non-AC Deluxe Twin Room";
    HRoom[15].Type = "Non-AC Deluxe Family Room";

    // assigning the costs for each room
    HRoom[0].CostPerNight = 12000;
    HRoom[1].CostPerNight = 17500;
    HRoom[2].CostPerNight = 15000;
    HRoom[3].CostPerNight = 20000;
    HRoom[4].CostPerNight = 15000;
    HRoom[5].CostPerNight = 20000;
    HRoom[6].CostPerNight = 18000;
    HRoom[7].CostPerNight = 24000;
    HRoom[8].CostPerNight = 8000;
    HRoom[9].CostPerNight = 10000;
    HRoom[10].CostPerNight = 13500;
    HRoom[11].CostPerNight = 16000;
    HRoom[12].CostPerNight = 10500;
    HRoom[13].CostPerNight = 15000;
    HRoom[14].CostPerNight = 17500;
    HRoom[15].CostPerNight = 18000;

    InitializeRooms(HRoom, NumRoom); // initiliazing all rooms

    std::cout << "Hello! Welcome to Moon Hotel!" << std::endl;         // program begins
    std::cout << std::endl;
    std::cout << "Please enter the username and password to log in to the system." << std::endl;
    std::cout << std::endl;

    // declaring variables
    std::string username;
    std::string password;
    int MaxLoginAttempt = 5;
    int LoginAttempt = 0;
    int BookingID = 0;
    int RID = 0;  // Room ID that user enters ; do not confuse with Room ID in struct Hotel_room

    while (LoginAttempt < MaxLoginAttempt)    // as long as LoginAttempt is less than max amount, system will let to log-in
    {
        std::cout << "Username: ";
        std::cin >> username;       // user inputs username
        std::cout << "Password: ";
        std::cin >> password;       // user inputs password
        std::cout << endl;

        if (username == "MoonHotel" && password == "MH257")      // assumption made and gave a username & password 
            // if both are correct, access to menu is granted
        {
            std::cout << "Log-in successful. Access granted!" << std::endl;
            std::cout << std::endl;

            int main_menu_opt = 0;     // user's choice for menu

            do
            {
                std::cout << "MOON HOTEL MENU : " << std::endl;
                std::cout << std::endl;
                std::cout << "1. View room details" << std::endl;  // viewing available rooms and booked ones, if any
                std::cout << "2. Search Room" << std::endl; // searching rooms by Room ID then if it is booked, we can view details of guest staying there
                std::cout << "3. Book rooms" << std::endl; // booking rooms
                std::cout << "4. View bookings" << std::endl; // viewing booked rooms
                std::cout << "5. Generate bill" << std::endl; // preparing bills  
                std::cout << "6. Exit Menu" << std::endl;    // leaving menu
                std::cout << std::endl;
                std::cout << "Please enter your option!" << std::endl;  // user's choice
                std::cout << "Option - ";

                std::cin >> main_menu_opt;
                std::cout << std::endl;

                switch (main_menu_opt)

                {
                case 1:
                {   // viewing available rooms and booked ones, if any
                    std::cout << "Room details." << std::endl;
                    std::cout << std::endl;
                    DisplayAvailableRoom(HRoom, NumRoom);     // all available rooms
                    DisplayBookedRoom(HRoom, NumRoom, CheckinDate, CheckoutDate);        // booked rooms, if there are any
                    std::cout << std::endl;                   // empty line
                }
                break;
                case 2:
                {
                    SearchbyRoomID(HRoom, NumRoom, RID);  // searching for room
                    std::cout << std::endl;  // empty line
                }
                break;
                case 3:
                {
                    BookRoom(HRoom, GuestDetails, NumRoom, BookingID, CheckinDate, CheckoutDate);  // booking room
                    std::cout << std::endl;   // empty line
                }
                break;
                case 4:
                {  // assumption made that booked and reserved rooms are the same
                    std::cout << std::endl;       // empty line
                    DisplayBookedRoom(HRoom, NumRoom, CheckinDate, CheckoutDate);  // viewing the bookings in hotel
                    std::cout << std::endl;       // empty line
                    std::cout << "If nothing appears, it means no rooms are booked just yet! You can choose option 3 to book rooms!" << std::endl;
                    std::cout << std::endl;  // empty line
                }
                break;
                case 5:
                {
                    std::cout << "Please enter the ID of the room which was booked - ";
                    std::cin >> RID;           // we need the Room ID to figure out the room type and its cost per night

                    if (IsRoomIDValid(RID, NumRoom))   // checking if room id is valid first
                    {
                        if (!HRoom[RID - 1].Room_status)   // whether room is booked or available 
                        {
                            std::cout << std::endl;
                            std::cout << "NOTE: If room was occupied any time after 6pm, it is counted as one night." << std::endl;
                            // because hotel offers night stays

                            OutputCheckinDate(CheckinDate);  // receptionist knows from which date to calculate
                            OutputCheckoutDate(CheckoutDate);   // receptionist knows until which date to calculate
                            std::cout << std::endl;                   // empty line

                            int NumNights = 0;            // duration of stay
                            std::cout << "Enter number of nights spent - ";
                            std::cin >> NumNights;
                            std::cout << std::endl;      // empty line

                            if (NumNights > 0)
                            {
                                double AddCharges = 0;           // any additonal charges for services guest spent
                                std::cout << "Please enter any additional charges, if there - ";
                                std::cin >> AddCharges;
                                std::cout << std::endl;         // empty line

                                if (AddCharges >= 0)
                                {
                                    GenerateBill(HRoom[RID - 1], NumNights, AddCharges, GuestDetails);
                                    std::cout << std::endl;     // empty line
                                }
                                else
                                {   // numbers less than 0 are not possible to be charged
                                    std::cout << "Invalid because it is a negative number." << std::endl;
                                    std::cout << std::endl;
                                }
                            }
                            else 
                            {
                            std:; cout << "Number of nights has to be greater than 0!" << std::endl;
                                std::cout << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Room has not been booked yet!" << std::endl;
                            std::cout << std::endl;  // empty line
                        }
                    }
                    else
                    {
                        std::cout << "Invalid Room ID! There are only rooms numbered between 1-16! Please try again." << std::endl;
                        std::cout << std::endl;   // empty line
                    }
                    break;
                }
                case 6:
                {
                    std::cout << "Exiting the menu.." << std::endl;
                    std::cout << std::endl;   // empty line
                }
                break;
                default:
                    std::cout << "Invalid option. Please try again!" << std::endl;   // options can only be between 1-6
                    return 1;
                }

            } while (main_menu_opt != 6);   // loop will continue as long as option is not 6, which is to exit menu
            return 0;
        }
        else
        {
            LoginAttempt++;
            std::cout << "Invalid log-in details. Please try again." << std::endl;    // username or/and password invalid
            std::cout << std::endl;   // empty line
            // system stops
        }

    }
    if (LoginAttempt == MaxLoginAttempt)  // if login attempts reaches max, program will end
    {
        std::cout << "Too many login attempts! Try again in 30 seconds." << std::endl;
    }
    return 0;
}


