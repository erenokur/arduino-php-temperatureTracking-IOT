
<?php
  include_once('seminer-database.php');

  $api_key_value = "tPmAT5Ab3j7F9";

  $api_key= $sensor = $location = $value1 = $value2 = $value3 = "";
  foreach($_POST as $key=>$post_data){
    echo "You posted:" . $key . " = " . $post_data . "<br>";
  }
  if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
 
    if($api_key == $api_key_value) {
      $sensor = test_input($_POST["sensor"]);
      $location = test_input($_POST["location"]);
      $value1 = test_input($_POST["value1"]);
      $value2 = test_input($_POST["value2"]);
      $value3 = test_input($_POST["value3"]);

      $result = insertReading($sensor, $location, $value1, $value2, $value3);
      echo $result;
    }
    else {
      echo "Wrong API Key provided.";
    }
  }
  else {
    echo "No data posted with HTTP POST.";
  }

  function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
  }
