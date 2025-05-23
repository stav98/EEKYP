# EEKYP
Αποθετήριο με οδηγίες κατασκευής, πηγαίο κώδικα και σχέδια για το έργο <b>"Εξοικονόμηση Ενέργειας και Υδάτινων Πόρων στο δημόσιο σχολείο"</b><br>
**Ομάδα:** Ομάδα ρομποτικής Ε.Κ. Πρέβεζας - 1ου ΕΠΑ.Λ. Πρέβεζας<br/>
**Σχολείο:** Ε.Κ. Πρέβεζας - 1ο ΕΠΑ.Λ. Πρέβεζας (2024-25)<br/>
**Τίτλος έργου:** Εξοικονόμηση Ενέργειας και Υδάτινων Πόρων στο δημόσιο σχολείο<br/> 

<b>Τελευταία ενημέρωση 19-5-2025</b>

Περιγραφή έργου
========================
Η ομάδα μας στα πλαίσια του <a href="https://openedtech.ellak.gr/">7ου Πανελλήνιου Διαγωνισμού Ανοιχτών Τεχνολογιών στην Εκπαίδευση</a> ο οποίος διοργανώνεται από τον <a href="https://eellak.ellak.gr/">ΕΕΛΛΑΚ</a> και με θεματική ενότητα <b>"Ανοιχτή Σχεδίαση για έναν Άμεσο Δημόσιο Χώρο"</b> υλοποίησε ένα σύστημα εποπτείας και διαχείρισης ενέργειας και νερού για το σχολείο μας. Το σύστημα τοποθετήθηκε στους χώρους του εργαστηριακού κέντρου (Ε.Κ.) και λειτουργεί δοκιμαστικά. 

Συγκεκριμένα το σύστημα έχει δομηθεί στους τέσσερις ακόλουθους άξονες και στο σχήμα φαίνεται ο τρόπος λειτουργίας και η επικοινωνία των μονάδων:
<ul>
 <li>Α. Εξοικονόμηση νερού</li>
 <li>Β. Εξοικονόμηση ενέργειας</li>
 <li>Γ. Μετεωρολογικός σταθμός</li>
 <li>Δ. Κεντρικό σύστημα διαχείρισης</li>
</ul>

<p align = "center">
<img src="/resources/images/system.png" height="500">
</p>

Περιεχόμενα
===========

<a href="/documentation/protasi.md">Αρχική πρόταση - Στόχοι - Λίστα υλικών - Προϋπολογισμός</a><br>
<a href="/documentation/eisagogi.md">Γενικές πληροφορίες</a><br>
<a href="Subsystem1_Irrigation/readme.md">Α. Εξοικονόμηση νερού</a><br>
<a href="Subsystem2_PowerSaving/readme.md">Β. Εξοικονόμηση ενέργειας</a><br>
<a href="Subsystem3_WeatherStation/readme.md">Γ. Μετεωρολογικός σταθμός</a><br>
<a href="Subsystem4_NodeRed/readme.md">Δ. Κεντρικό σύστημα διαχείρισης</a><br>

Συμμετέχοντες μαθητές
=====================
Οι μαθητές προέρχονται από το 1ο ΕΠΑ.Λ. Πρέβεζας και από τους τομείς Πληροφορικής - Ηλεκτρολογίας.
<ul>
 <li>Αργυρός Θεμιστοκλής</li>
 <li>Αδάμ Ευάγγελος</li>
 <li>Νάτση Παυλίνα</li>
 <li>Κόκκας Παναγιώτης</li>
</ul>

Υπεύθυνοι καθηγητές: Σταύρος Φώτογλου ΠΕ86 πληροφορικής, Κοτζαμουράτογλου Γιώργος ΠΕ83 ηλεκτρολογίας

Για την υλοποίηση του έργου χρησιμοποιήθηκε ο εξοπλισμός των εργαστηρίων του Εργαστηριακού Κέντρου (Ε.Κ.) Πρέβεζας. Τα υλικά που χρησιμοποιήθηκαν ήταν δωρεά του ΕΕΛΛΑΚ.
<p>Χρησιμοποιήθηκε αποκλειστικά λογισμικό ανοιχτού κώδικα.</p>
<ul>
 <li>Λειτουργικό σύστημα Linux. Στους σταθμούς εργασίας στους οποίους έγινε ο σχεδιασμός, ανάπτυξη του έργου υπήρχε εγκατεστημένο Ubuntu 24.04 Mate.</li>
 <li>Draw.io για σχεδιαμό διαγραμμάτων, κυκλωμάτων.</li>
 <li>FreeCad για σχεδιαμό των τρισδιάστατων μοντέλων.</li>
 <li>Gimp για επεξεργασία φωτογραφιών.</li>
 <li>Audacity για επεξεργασία ήχου.</li>
 <li>Simple Screen Recorder για σύλληψη video από την επιφάνεια εργασίας.</li>
 <li>OpenShot για επεξεργασία video.</li>
 <li>LibreOffice για τα κείμενα και εξαγωγή PDF.</li>
 <li>PlatfomIO μαζί με VsCode για την ανάπτυξη του λογισμικού.</li>
 <li>Ubuntu Linux 24.04 server στον εικόνικο διακομιστή με το Mosquitto MQTT brocker και το NodeRed. Επίσης στον φυσικό διακομιστή λειτουργεί Ubuntu 24.04 Server με KVM για εικονικά συστήματα και Docker για τα container.</li> 
</ul>

Χρονοδιάγραμμα - Στάδια υλοποίησης του έργου
===========================
