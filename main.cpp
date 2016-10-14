#include <stdio.h>
#include <stdlib.h>


int i = 0 , j = 0 , first_reserv = 0 , economy_reserv = 0  ; /*Δήλωση μεταβλητών */
char input ; 
int seats[10][4] = {0} ;

void choice( char a );  /*Δήλωση πρότυπων συναρτήσεων */
void first_class_reservation();
void eco_class_reservation();
char row( int b );


int main ()          /*Έναρξη της Main*/
{

	FILE* fp ;  

	while (( first_reserv < 20 ) || ( economy_reserv < 20 ))  /* while για δημιουργία βρόχου μέχρι να γεμίσουν οι θέσεις */
		{
			printf ( "Insert :\n F for first class reservation \n E for economy class reservation \n or Q to display the current reservations and quit this application. \n " );
			input = getchar();
			fflush(stdin);
			if (( input != 'Q' ) && ( input != 'q' ))  
				choice(input);  /* Κλήση της Choise για την επεξεργασία της επιλογής */
			else 
				break; /* Τερματισμός βρόχου όταν δοθεί η επιλογή Q */
		}

		printf ( "On First Class %d seats have been booked. \nOn economy class %d seats have been booked.\nThe seats reserved are :\n", first_reserv, economy_reserv );
		printf ( "\tA Row: \t\tB Row: \t\tC Row: \t\tD Row: \n\nFirst Class:\n\n" );
		for ( i = 0 ; i < 5 ; i++ )
		{
			for ( j = 0 ; j < 4 ; j++ )
			{
				if ( (seats[i][j]) == 1 )
					printf ( "\t%d%c\t", i + 1 , row(j)) ;    /*Αναζήτηση στον πίνακα για την εύρεση των θέσεων με τιμή 1 ( δηλάδη για τις κρατημένες θέσεις ) Εδώ γίνεται αναζήτηση για την πρώτη θέση */
				else 
					printf ( "\tEmpty\t" );
			}
			printf ( "\n" ) ;
		}
		printf ( "\n Economy Class: \n\n");
		for ( i = 5 ; i < 10 ; i++ )
		{
			for ( j = 0 ; j < 4 ; j++ )
			{
				if ( (seats[i][j]) == 1 )
					printf ( "\t%d%c\t", i + 1 , row(j)) ;      /*Εδώ γίνεται αναζήτηση για την Οικονομική θέση*/
				else 
					printf ( "\tEmpty\t" );
			}
			printf ( "\n" ) ;
		}

		if ( (fp = fopen( "reservations.txt" , "a+" )) == NULL )   /*’νοιγμα του αρχείου και έλενχος αν άνοιξε*/
			{
				printf ( "\nThere was a problem saving the file. \nPress any key to continue . . ." );
				fflush(stdin);
				getchar();
				return 0;  
			}
		fprintf ( fp,"On First Class %d seats have been booked. \nOn economy class %d seats have been booked.\n\n" , first_reserv, economy_reserv ); /*Εγγραφή στο αρχείο*/
		for ( i = 0 ; i < 5 ; i++ )
		{
			for ( j = 0 ; j < 4 ; j++ )
			{
				if ( (seats[i][j]) == 1 )
					fprintf ( fp, "\t%d%c\t", i + 1 , row(j)) ;
				else 
					fprintf ( fp, "\tEmpty\t" );
			}
			fprintf ( fp, "\n" ) ;
		}
		fprintf ( fp, "\n Economy Class: \n\n");
		for ( i = 5 ; i < 10 ; i++ )
		{
			for ( j = 0 ; j < 4 ; j++ )
			{
				if ( (seats[i][j]) == 1 )
					fprintf ( fp, "\t%d%c\t", i + 1 , row(j)) ;
				else 
					fprintf ( fp, "\tEmpty\t" );
			}
			fprintf ( fp, "\n" ) ;
		}

		printf ( "\nSaved on ""reservations.txt"" successfuly! \nPress any key to continue . . ." );  
		fclose ( fp );
		fflush(stdin);
		getchar();
		return 0 ;                                                /*Κλείσιμο αρχείου και έξοδος από το πρόγραμμα*/
		}

void choice( char a ) 
	{
		switch ( a ) {      /*Switch για δημιουργία επιλογών*/
		case 'F': 
		case 'f':
			if ( first_reserv < 20 )
				first_class_reservation();
			else
			{ 
				printf ( " All seats on first class are currently booked! \n Would you like an economy class seat? \n ( Press Y for Yes, N for No or any other key for main menu ) " );
				char temp ;
				temp = getchar() ;                        
				fflush(stdin);
				if (( temp == 'Y' ) || ( temp == 'y' ))  /* Σε περίπτωση που είναι κρατημένες όλες οι θέσεις στην πρώτη θέση το πρόγραμμα ρώταει τον χρήστη αν θέλει*/
					eco_class_reservation();			 /* Κράτηση στην οικονομική θέση*/
				else if (( temp == 'N') || ( temp == 'n' )) 
					printf ( "Next flight is after 4 hours." );
			}	
			break;
		case 'E': 
		case 'e':
			if ( economy_reserv < 20 )
				eco_class_reservation();
			else
			{ 
				printf ( " All seats on economy class are currently booked! \n Would you like an first class seat? \n ( Press Y for Yes, N for No or any other key for main menu ) " );
				char temp ;
				temp = getchar() ;
				fflush(stdin);
				if (( temp == 'Y' ) || ( temp == 'y' ))  /*Όπως και πριν, το πρόγραμμα ρώταει τον χρήστη αν θέλει κράτηση στην άλλη θέση*/
					first_class_reservation();
				else if (( temp == 'N') || ( temp == 'n' )) 
					printf ( "Next flight is after 4 hours." );
			}			
			break;
		default: 
			printf ( "Invalid input. Please try again. \n" ) ;
			break;
	}
	}

void first_class_reservation()  /*Συνάρτηση για κράτηση στην πρώτη θέση*/
	{ 
		first_reserv++;
				for ( i = 0 ; i < 5 ; i++ ) 
					{ 
						for ( j = 0 ; j < 4 ; j++ )
						{
							if ( seats[i][j] == 0 )      /*Γίνεται αναζήτηση στον πίνακα για τιν εύρεση κελιού με το στοιχείο 0 και στην συνέχεια αλλαγή αυτού σε 1 */
							{
								seats[i][j] = 1 ;
								goto out ;
							}
						}
					}
				out:
				printf ( "Seat reserved: \n ");
				printf ( " %d%c , First Class. \n", i + 1 , row(j) );

	}

void eco_class_reservation()	/*Συνάρτηση για κράτηση στην οικονομική θέση*/
	{ 
		economy_reserv++;
				for ( i = 5 ; i < 10 ; i++ ) 
				{ 
						for ( j = 0 ; j < 4 ; j++ )
						{
							if ( seats[i][j] == 0 )
							{
								seats[i][j] = 1 ;
								goto out ;
							}
						}
				}
				out:
				printf ( "Seat reserved: \n ");
				printf ( " %d%c , Economy Class. \n", i + 1 , row(j) );
	}
		
char row( int b )			/*Συνάρτηση που μετατρέπει τα νούμερα που δηλώνουν την στήλη στον πίνακα με το αντίστοιχο γράμμα στις θέσεις*/
{
	if ( b == 0 )
		return 'A' ;
	else if ( b == 1 )
		return 'B' ;
	else if ( b == 2 )
		return 'C' ;
	else
		return 'D' ;
}