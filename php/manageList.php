<!DOCTYPE HTML>
<html>

<head>
    <meta http-equiv="content-type" content="text/html; charset=utf-8" />
    <link rel="stylesheet" href="./css/style.css" type="text/css" />
    <title>Naughty or Nice List</title>

</head>

<body>
    <h1>Add a Person to the Naughty or Nice List!</h1>
    <!-- <h2>Your almost ready to use our fabulous product, just fill out this form!</h2> -->
    <hr />
    <?php
        $success = false;
        include './listFunctions.inc';
        if (isset($_POST['submit'])) {
        // Run the following if the form has previously been submitted
            $success = main();
            echo "<div id=\"errorWords\" style=\"display: hidden\">";
            echo $errorMessage;
            echo "</div>";
        }
            
        if(!$success) {
        // If the form did not pass validation (or its the first time running), end the PHP script.
    ?>
        <br />
        <!-- Values is set to the users input if the input was valid, and '' if it was not.
                 If it retuned as '', set the class to error.  -->
        <form action='' method="post">
            <label for="personalId">Personal Identifier: </label> <br />
            <input type="text" name="personId" id="personId" value="<?php echo $values['personId'] ?>"
                class="<?php if (isset($_POST['submit'])) { echo hasError($values['personId']);} ?>"
                   placeholder="e.g. 001" />
            <br /><br />

            <label for="firstName">First Name: </label> <br />
            <input type="text" name="firstName" id="firstName" value="<?php echo $values['firstName'] ?>"
                class="<?php if (isset($_POST['submit'])) { echo hasError($values['firstName']);} ?>"
                   placeholder="e.g. Taylor" />
            <br /><br />

            <label for="lastName">Last Name: </label> <br />
            <input type="text" name="lastName" id="lastName" value="<?php echo $values['lastName'] ?>"
                class="<?php if (isset($_POST['submit'])) { echo hasError($values['lastName']);} ?>"
                   placeholder="e.g. Smith"/>
            <br /><br />

            <label for="age">Age: </label> <br />
            <input type="text" name="age" id="age" value="<?php echo $values['age'] ?>" maxlength="2"
                class="<?php if (isset($_POST['submit'])) { echo hasError($values['age']); } ?>"
                   placeholder="e.g. 12" />
            <br /><br />

            <label for="city">City: </label> <br />
            <input type="text" name="city" id="city" value="<?php echo $values['city'] ?>"
                   class="<?php if (isset($_POST['submit'])) { echo hasError($values['city']); } ?>"
                    placeholder="e.g. Ottawa"/>
            <br /><br />

            <label for="curList">Current List: </label> <br />
            <select name="curList" id="curList" class="<?php if (isset($_POST['submit'])) { echo hasError($values['curList']); } ?>">
                    <option value="G">Good</option>
                    <option value="N">Naughty</option>
                    <option value="L">Limbo</option>
                    <option value="U">Unknown</option>
            </select>
            <br /><br />

            <label for="details">Details: </label> <br />
            <textarea name="details" id="details" rows="8" cols="40" spellcheck="true" maxlength="500"
                      placeholder="Enter relevant details here: "></textarea>
            <br /><br />

            <input type="submit" name="submit" id="submit" value="Add Person">
        </form>
        <?php
            } else {
            echo "<p>Thanks for registering! You will recieve an email when your account is ready.</p>";
            }
?>
            <hr />
            <p>&#169; 2016 Santa's Workshop, The North Pole, H0H 0H0</p>
</body>

</html>
