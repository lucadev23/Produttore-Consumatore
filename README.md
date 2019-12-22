# Problema Produttore-Consumatore

<p><h2>Esercizio Produttore-Consumatore</h2></p>
<ul>
  <li>Sviluppare due processi (un consumatore e un produttore) NON IMPARENTATI che condividono un file</li>
  <li>Produttore:
    <ul>
      <li>permette all'utente di immettere una stringa che viene scritta nel file</li>
      <li>il file viene sovrascritto ad ogni produzione (contiene dunque solo una stringa)</li>
    </ul>
  </li>
  <li>Consumatore:
    <ul>
      <li>legge dal file la stringa in essa contenuta</li>
      <li>stampa a video tali stringhe</li>
    </ul>
  </li>
 <li>I processi terminano quando l'utente inserisce la parola "end"</li>
  <ul><li>
  che viene scritta nel file per poter essere letta dal consumatore
  </li></ul>
</ul>
<p><h2>Soluzione</h2></p>
La soluzione prevede l'uso di 2 semafori
<ul>
  <li>WRITE</li>
  <li>READ</li>
</ul>
Usiamo due semafori System V (array monodimensionali)
<ul>
  <li>WRITE (inizializzato a 1)</li>
  <li>READ (inizializzato a 0)</li>
</ul>
