<?php
// errorMessage is set to empty string to start.
$errorMessage = '';
// An associative array of all of the fields on the page and their data.
$values = array(
                "personId"      => "",
                "firstName"     => "",
                "lastName"      => "",
                "age"           => "",
                "curList"       => "",
                "city"          => "",
                "details"       => "",
                "dateUpdated"   => "" 
               );

 function main() {
    // The main function that calls all the other functions.
    // Returns TRUE if no errors are found, and FALSE if errors are found.
    global $values;
    global $errorMessage; 
    global $values;

    $values = array(
                    "personId"  => $_POST['personId'],
                    "firstName" => $_POST['firstName'],
                    "lastName"  => $_POST['lastName'],
                    "age"       => $_POST['age'],
                    "curList"   => $_POST['curList'],
                    "city"      => $_POST['city'],
                    "details"   => $_POST['details']
                    );

    $success = TRUE;
    $errorEnding = ' Please enter a proper value' . '<br />';
    
    foreach($values as $key => $input) {
        // Trims each value
        $values[$key] = trim($input);
    } 

    if(validateExists($values['personId']) == FALSE) {
        $errorMessage .= "Personal Identification  is empty. $errorEnding";
        $values['personalId'] = "";
        $success = FALSE;
    }

    if(validateExists($values['firstName']) == FALSE) {
        $errorMessage .= "First name is empty. $errorEnding";
        $values['firstName'] = "";
        $success = FALSE;
    }

    if(validateExists($values['lastName']) == FALSE) {
        $errorMessage .= "Last name is empty." . $errorEnding; 
        $values['lastName'] = "";
        $success = FALSE;
    }

    if(validateExists($values['age']) == FALSE) {
        $errorMessage .= "Age is empty." . $errorEnding; 
        $success = FALSE;
        $values['age'] = "";
    }

     if(validateExists($values['city']) == FALSE) {
         $errorMessage .= "City is empty." . $errorEnding;
         $success = FALSE;
         $values['city'] = "";
     }

     if ($success) {
        writeToFile();
        return $success; 
    } else {
        return $success;
    }
}
 

function validateExists($data) {
    // Makes sure the data is not empty.
    if($data != '') {
        return TRUE;
    } else {
        return FALSE;
    }
}

function hasError($data) {
    // Determins if the data had an error or not.
    global $values;
    if($data == "") {
        return "error";
    } else {
        return "";
    }
}

function writeToFile() {
    // Writes everything in the array $values to the file accounts.txt
    global $values;
    $foundReplace = false;
    $fileName = './List/SantaList.json';
    $jsonArray = array();

    $currPerson = array (     '-id'  => trim($_POST['personId']),
                        'firstName'  => $_POST['firstName'],
                         'lastName'  => $_POST['lastName'],
                              'age'  => $_POST['age'],
                             'city'  => $_POST['city'],
                          'curList'  => $_POST['curList'],
                          'details'  => $_POST['details'],
                      'dateUpdated'  => date('dd \- mm -\ Y'));

    $jsonFile = file_get_contents($fileName);

    $jsonArray = json_decode($jsonFile, true);

    // foreach ($jsonArray['person'] as $key) {
    //     var_dump($key);
    //     if ($key['-id'] === $currPerson['-id']) {
    //         echo '<br />';
    //         echo '<br />';
    //         var_dump($key['-id']);
    //         foreach ($key as $input => $output) {
    //             echo '<br />';
    //             echo '<br />';
    //             var_dump($jsonArray['person'][$input]);
    //             $jsonArray['person'][$input] = $currPerson[$input];
    //             var_dump($jsonArray['person'][$input]);
    //         }
    //         $foundReplace = true;
    //     }
    // }
    //
    // if ($foundReplace === false) {
    //     array_push($jsonArray['person'], $currPerson);
    //     echo 'New Person Added';
    // }
    //
    // echo '<br />';
    // echo '<br />';
    //
    // var_dump($jsonArray);

    array_push($jsonArray['person'], $currPerson);

    $jsonFile = json_encode($jsonArray, JSON_PRETTY_PRINT);

    file_put_contents($fileName, $jsonFile);
}

function getIDs() {
    $idFile = file('./List/idList.txt');
    $lastID = "";

    foreach ($idFile as $num) {
        $lastID  = $num;
        echo "<option name='$num' value='$num''>$num</option>";
    }
    $lastID = $lastID + 1;
    echo "<option name='$lastID' value='$lastID' selected>$lastID</option>";

}

function fillForms() {
    global $values;
    $fileName = './List/SantaList.json';
    $jsonFile = file_get_contents($fileName);
    $jsonArray = json_decode($jsonFile, true);
    $found = FALSE;

    foreach ($jsonArray['person'] as $value)
    {
        if ($value['-id'] == trim($_POST['personId'])) {
            $values = array("personId"  => trim($_POST['personId']),
                            "firstName" => $value['firstName'],
                            "lastName"  => $value['lastName'],
                            "age"       => $value['age'],
                            "curList"   => $value['curList'],
                            "city"      => $value['city'],
                            "details"   => $value['details']);
        }
    }
    return $found;
}
