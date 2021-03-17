<!doctype html>
<html>
	<head>
		<meta charset="utf-8">
	    <meta http-equiv="X-UA-Compatible" content="IE=edge">
	    <meta name="viewport" content="width=device-width, initial-scale=1">
		<title>IOT Light</title>
		<link rel="stylesheet" type="text/css" href="style.css">
		<link rel="stylesheet" type="text/css" href="bootstrap.min.css">
	</head>
	<body>
		<h3 align="center">CONTROL PANEL</h3>
		<div class="container fluid">
			<div class="row">
			  	<div class="col-md-6 thumbnail">
			  		<h1> ROOM 1</h1>
						<form action = "lightroom.php" method="get">
							<table style=" margin-left: 220px;">
								<tr><td><input type = "submit" name = "lightOn" value = "Turn on"></td></tr>
								<tr><td><input type = "submit" name = "lightOff" value = "Turn off"></td></tr>
							</table>
						</form><br>
						<p align="center">STATUS = ""</p>
			  	</div>
			  	<div class="col-md-6 thumbnail">
			  		<h1> ROOM 2</h1>
				  		<form action = "lightroom.php" method="get">
							<table style=" margin-left: 220px;">
								<tr><td><input type = "submit" name = "lightup" value = "Turn on"></td></tr>
								<tr><td><input type = "submit" name = "lightdown" value = "Turn off"></td></tr>
							</table>
						</form><br>
						<p align="center">STATUS = ""</p>
			  	</div>
		</div>
		<?php
		$db_host = "localhost";
		$db_user = "laxus";
		$db_pass = "Laxus#1996";
		$db_name = "iot";
		$connect = mysqli_connect($db_host, $db_user, $db_pass, $db_name);
		if( mysqli_connect_errno($connect) ){
			echo "Failed to connect to MySQL: " . mysqli_connect_error();
			exit();
		}
	  if(isset($_GET['lightOn'])){
	  	mysqli_query($connect,"update room_one set status_one='room_one_on'");
	  }
	  if(isset($_GET['lightOff'])){
	  	mysqli_query($connect,"update room_one set status_one='room_one_off'");
	  }
		if(isset($_GET['lightup'])){
			mysqli_query($connect,"update room_two set status_two='room_two_on'");
		}
		if(isset($_GET['lightdown'])){
			mysqli_query($connect,"update room_two set status_two='room_two_off'");
		}
		if( $result = mysqli_query($connect, "select * from room_one") ){
			$row = mysqli_fetch_assoc($result);
	    echo "<h4>".$row['status_one']."</h4>";
		}
		if( $result = mysqli_query($connect, "select * from room_two") ){
			$row = mysqli_fetch_assoc($result);
	    echo "<h4>".$row['status_two']."</h4>";
		}
		mysqli_close($connect);
		?>
	</body>
</html>
