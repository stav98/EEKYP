<H2>Α. Εξοικονόμηση νερού</H2>
Σχεδιάσαμε και κατασκευάσαμε μονάδα αυτόματου ποτίσματος με αισθητήρες υγρασίας και θερμοκρασίας στην ρίζα των φυτών ώστε να ποτίζονται αυτόματα μόνο όταν είναι απαραίτητο. Αν και στον αρχικό σχεδιασμό σκοπευαμε να κατασκευάσουμε τουλάχιστον δύο μονάδες, τελικά κατασκευάσαμε μία διπλή. Η μονάδα υποστηρίζει δύο ανεξάρτητες γραμμές ποτίσματος με ανεξάρτητους αισθητήρες και τοποθετήθηκε στον κήπο του Ε.Κ. Οι μονάδες αυτές επικοινωνούν μέσω διαδικτύου με το κεντρικό σύστημα διαχείρησης. 
Ακολουθεί το block διάγραμμα της μονάδας
<p align = "center">
  <img src="../resources/images/A_Water.png" width="500">
</p>
<H3>Κατασκευή ηλεκτρονικού κυκλώματος</H3>
Έγινε κατασκευή του πρωτοτύπου σε διάτρητη πλακέτα perfboard. Πάνω στην πλακέτα τοποθετήθηκαν όλα τα εξαρτήματα και τα αρθρώματα και κολλήθηκαν από την κάτω πλευρά με λεπτά σύρματα. Ακολουθεί το θεωρητικό κύκλωμα της μονάδας.
<p align = "center">
  <img src="schematics/EEKYP1.png" width="700">
</p>
Κόλληση των εξαρτημάτων και αρθρωμάτων σύμφωνα με το προηγούμενο σχέδιο
<table align="center">
 <tr>
  <td><img src="Images/EEKYP1_pcb_construction1.jpg" width="300"></td>
  <td><img src="Images/EEKYP1_pcb_construction2.jpg" width="300"></td>
  </tr>
</table>
Το τελικό αποτέλεσμα και οι ηλεκτρολογικές συνδέσεις των αισθητήρων - ενεργοποιητών
<table align="center">
 <tr>
  <td><img src="Images/EEKYP1_pcb.jpg" width="300"></td>
  <td><img src="Images/EEKYP1_Connections.jpg" width="300"></td>
  </tr>
</table>
<H3>Σχεδιασμός και εκτύπωση συστήματος ηλεκτροβάνας</H3>
Επειδή οι ηλεκτροβάνες άρδευσης είναι ακριβές και οι φθηνότερες βαλβίδες λειτουργούν μόνο σε δύο καταστάσεις (ανοιχτό/κλειστό) αποφασίσαμε να χρησιμοποιήσουμε απλές βάνες (κόστος περίπου 1€) και να τις περιστρέφουμε με servo κινητήρα. Για τον λόγο αυτό σχεδιάσαμε στο Freecad μια απλή βάση στήριξης της βάνας και του servo motor. Τα αρχεία σε μορφή stl <a href="3D">βρίσκονται εδώ</a>.
<table align="center">
 <tr>
  <td><img src="Images/EEKYP1_Valves.jpg" width="350"></td>
  <td><a href="https://youtu.be/jAH-wysm_M4?si=AJ5Le6BRvx6Hh9Bs" title="Παρακολούθηση video"><img src="https://i.ytimg.com/vi/jAH-wysm_M4/maxresdefault.jpg" width="300"></a>
  </td>
  </tr>
</table>
<H3>Προγραμματισμός</H3>
Η μονάδα έχει δύο modules με microcontrollers. Το Arduino Nano και το ESP01. Το πρώτο δέχεται τα σήματα των αισθητήρων και ελέγχει τους ενεργοποιητές, ενώ το δεύτερο είναι υπεύθυνο για την σύνδεση στο διαδίκτυο μέσω WiFi και γενικά κάνει την περισσότερη δουλειά. Τα δύο modules επικοινωνούν μέσω σειριακής θύρας σε ρυθμό 9600bps. Ο κώδικας είναι γραμμένος σε C++ (Arduino wiring) και χρησιμοποιήσαμε το IDE vscode με την επέκταση του PlatformIO. Επίσης στο ESP01 λειτουργεί και ένας mini Web Server γι' αυτό έχουμε και λίγο κώδικα σε HTML καθώς και JQuery - JavaScript.
<H3>Δοκιμές</H3>
Έγιναν πολλές δοκιμές και πολλές διορθώσεις μέχρι να πετύχουμε ικανοποιητικά αποτελέσματα. Αρχικά δοκιμάσαμε μέσα στο εργαστήριο την επικοινωνία με το διαδίκτυο, τους αισθητήρες, την κίνηση των ηλεκτροβανών και μετά έγιναν οι δοκιμές σε εξωτερικό περιβάλλον.
<table align="center">
 <tr>
  <td><img src="Images/EEKYP1_irigation_test.jpg" width="300"></td>
  <td><img src="Images/EEKYP1_Test1.jpg" width="300"></td>
  <td><a href="https://youtu.be/mC_GyszawEE?si=4FmsMeqU08K2Nvmm" title="Παρακολούθηση video"><img src="https://i.ytimg.com/vi/mC_GyszawEE/maxresdefault.jpg" width="300"></a>
  </td> 
  </tr>
</table>
<H3>Μηχανολογική κατασκευή - Τοποθέτηση σε αδιάβροχο ηλεκτρολογικό κουτί</H3>
Με την βοήθεια του μαθητή από τον ηλεκτρολογικό τομέα έγινε η κατασκευή του κουτιού. Επειδή η μονάδα λειτουργεί σε εξωτερικό χώρο πρέπει να είναι προστατευμένη από υγρασία. Να επισημάνουμε ότι η μονάδα λειτουργεί με μέγιστη τάση έως 24V επομένως δεν υπάρχει απολύτως κανένας κίνδυνος ηλεκτροπληξίας.
<table align="center">
 <tr>
  <td><img src="Images/EEKYP1_Box1.jpg" width="300"></td>
  <td><img src="Images/EEKYP1_Box2.jpg" width="300"></td>
  <td><img src="Images/EEKYP1_Box3.jpg" height="200"></td>   
 </tr>
</table>
<table align="center">
 <tr>
  <td><a href="https://youtu.be/40IbOIiYmcU" title="Παρακολούθηση video"><img src="https://i.ytimg.com/vi/40IbOIiYmcU/maxresdefault.jpg" width="300"></a>
  </td>
  <td><a href="https://youtube.com/shorts/qObYvg2sueE?si=E88Q5BgSeAc8Eiv0" title="Παρακολούθηση video"><img src="https://i.ytimg.com/vi/qObYvg2sueE/maxres2.jpg" height="160"></a>
  </td> 
  </tr>
</table>
<table align="center">
 <tr>
  <td><img src="Images/EEKYP1_BOX4.jpg" height="160"></td>
  <td><img src="Images/EEKYP1_PCBinBOX.jpg" height="160"></td>  
 </tr>
</table>
<H3>Πέρασμα σωλήνων και καλωδίων και τελική τοποθέτηση της μονάδας</H3>
Πάλι με την βοήθεια του ηλεκτρολογικού τομέα, τοποθετήθηκαν τα λάστιχα και τα μπεκ στις ρίζες των φυτών και συνδέθηκαν οι αισθητήρες ώστε να γίνει η τελική δοκιμή.
Η μονάδα σε λειτουργία στο αίθριο του Ε.Κ. Πρέβεζας.
<p align = "center">
  <img src="Images/EEKYP1_System.jpg" height="400">
</p>
<H3>Παρουσίαση της λειτουργίας του υποσυστήματος 1</H3>
Στον εσωτερικό κήπο του Ε.Κ. δοκιμάσαμε το σύστημα εξοικονόμησης νερού. Στα ακόλουθα video ο μαθητής παρουσιάζει την λειτουργία του.
<table align="center">
 <tr>
  <td><a href="https://youtu.be/C70y3Lhc9u4?si=_cwhh2kix79nuEjM" title="Παρακολούθηση video"><img src="https://i.ytimg.com/vi/C70y3Lhc9u4/maxresdefault.jpg" width="300"></a>
  </td>
  <td><a href="https://youtu.be/XpcmS4x5700?si=bWU8NFIqS5j7YiVU" title="Παρακολούθηση video"><img src="https://i.ytimg.com/vi/XpcmS4x5700/maxresdefault.jpg" height="160"></a>
  </td>
  </tr>
  <tr>
    <td> <span style="font-size: 1em">Παρουσίαση τοπικής διαχείρισης μέσω Web Interface<span></td>
    <td>Παρουσίαση κεντρικής διαχείρισης μέσω Node Red</td>
  </tr>
</table>
