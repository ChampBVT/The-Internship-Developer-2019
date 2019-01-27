<?php
  //Created by Borvorntat Nirandmongkol
  header('Content-Type: application/json');
  $xml = simplexml_load_file("weather.xml"); //load xml file
  $json=[];
  foreach($xml->children() as $child) // Children of current
  {
    $innerJson=[];
    foreach($child->attributes() as $a => $b) { //ex. Attributes of city -> id and name
      $innerJson[$a]=$b->__toString();
    }
    foreach($child->children() as $child1){  //ex. Children of city -> coord, country and sun
      $innerJson1=[];
      foreach($child1->attributes() as $a => $b) { // ex. Attributes of coord -> lon and lat
        $innerJson1[$a]=$b->__toString();
      }
      if(!empty($innerJson1)) 
        $innerJson[$child1->getName()] = $innerJson1;
      else if(!empty($child1))
        $innerJson[$child1->getName()]  = $child1->__toString(); // "country" : "GB" case (no children)
    }
    if(!empty($innerJson))
      $json[$child->getName()] = $innerJson;
    else if(!empty($child))
      $json[$child->getName()] = $child->__toString();
  }
  echo print_r($json);
  $fp = fopen('weather.json', 'w'); //create JSON 
  fwrite($fp, json_encode($json));
  fclose($fp);
?>
