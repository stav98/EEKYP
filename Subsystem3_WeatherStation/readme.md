<H3>Γ. Μετεωρολογικός σταθμός</H3>
Σχεδιάσαμε και κατασκευάσαμε έναν μετεωρολογικό σταθμό ο οποίος επικοινωνεί μέσω διαδικτύου με τον κεντρικό σύστημα διαχείρισης ώστε τα δεδομένα να χρησιμοποιούνται από τις προηγούμενες μονάδες. Τα περισσότερα όργανα του μετεωρολογικού σταθμού τα κατασκευάσαμε στον εκτυπωτή 3D του σχολείου.

Ακολουθεί το block διάγραμμα της μονάδας
<p align = "center">
  <img src="../resources/images/C_MeteoStation.png" width="500">
</p>
<H3>Κατασκευή ηλεκτρονικού κυκλώματος</H3>
Έγινε κατασκευή του πρωτοτύπου σε διάτρητη πλακέτα perfboard. Πάνω στην πλακέτα τοποθετήθηκαν όλα τα εξαρτήματα και τα αρθρώματα και κολλήθηκαν από την κάτω πλευρά με λεπτά σύρματα. Ακολουθεί το θεωρητικό κύκλωμα της μονάδας.
<p align = "center">
  <img src="schematics/EEKYP1.png" width="700">
</p>

Αποτελείται από τα παρακάτω όργανα:

## Ανεμόμετρο

Το ανεμόμετρο μετράει την ταχύτητα του ανέμου. Την ιδέα την βρήκαμε στο https://www.yoctopuce.com/EN/article/how-to-measure-wind-part-1 και τα αρχεία για την εκτύπωση 3D υπάρχουν στον κατάλογο 3D.

### Τροποποιήσεις

1. Ρουλεμάν. Τα δύο ρουλεμάν έχουν διαστάσεις 9mm(εξωτερ.), 5mm(εσωτερ.), 3mm(ύψος) και προέρχονται από κεφαλές παλαιών HDD 3,5".
2. Άξονας. Για άξονα χρησιμοποιήσαμε βίδα 5mm(4,9) και την κόψαμε σε μήκος 51mm. Στο κάτω άκρο χαράξαμε εγκοπή ώστε να μπαίνει πλακέ κατσαβίδι.
3. Επειδή υπάρχουν μικρά κενά στην εφαρμογή των ρουλεμάν με την φωλιά, κόβουμε κομμάτι αυτοκόλλητης αλουμινοταινίας 4,5mm x 100mm και τυλίγουμε 2-3 στροφές στην εξωτερική πλευρά των ρουλεμάν.
4. Το ίδιο γίνεται και στον άξονα στα δύο σημεία που εφάπτεται με τα ρουλεμάν. Ταινία αλουμινίου 6,5mm x 56mm και τυλίγουμε 2 στροφές στον άξονα.
5. Μεγαλώνουμε τις οπές στα καπάκια πάνω και κάτω σε διάμετρο 6,6 - 7mm ώστε να περνάει άνετα ο άξονας.
6. Στον εσωτερικό δίσκο με τις 4 σχισμές μεγαλώνουμε την κεντρική οπή σε 4mm και με σπειροτόμο 5mm κάνουμε στροφές. Για σταθεροποίηση, από την πάνω πλευρά βάζουμε ροδέλα στην οποία έχουμε κάνει στροφές και βιδώνει κόντρα.
7. Στον ρότορα με τα κουτάλια μεγαλώνουμε την οπή σε 4mm και κάνουμε στροφές.
8. Ο εσωτερικός δίσκος βιδώνεται στον άξονα. Το ίδιο γίνεται και στον ρότορα κρατώντας με κατσαβίδι πλακέ τον άξονα από κάτω.
9. Για φωτοδίοδο και φωτοτρανζίστορ χρησιμοποιούμε το υπέρυθρο TCRT5000. Βγάζουμε τα δύο στοιχεία από το πλαστικό πλαίσιο και βάζουμε το φωτοτρανζίστορ από την πάνω πλευρά και την φωτοδίοδο από την κάτω.
10. Η φωτοδίοδος συνδέεται στα +5V μέσω αντιστάτη 220Ω και ο συλλέκτης του τρανζίστορ πάει στα +5V. Στην πλακέτα ο εκπομπός γειώνεται μέσω αντιστάτη pulldown 1Κ.

Για την σύνδεση με την πλακέτα θέλουμε 3 καλώδια (5V, GND και τα δεδομένα από τον εκπομπό του φωτοτρανζίστορ που είναι παλμοί μεταβλητής συχνότητας ανάλογα με την ταχύτητα περιστροφής του ρότορα.)

