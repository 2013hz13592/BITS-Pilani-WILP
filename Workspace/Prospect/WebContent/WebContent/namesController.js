var app=angular.module('myApp', []);
var crumbs=[];
app.controller('namesCtrl', function($scope, $http, $location) {
	//$scope.names=
	//[
	// 	{name:'Hege',country:'Sweden'},
	//	{name:'Kai',country:'Denmark'}
	//];
	//$http.get("/names.json").success(function(data){
	//	 alert('hello');
	//	 $scope.names=data;
	//}).error(function(){alert('error');});
	
	$scope.imgAlt='D';
	$scope.imgSrc='A';
	$scope.imgSrcAlt=$scope.imgAlt+$scope.imgSrc;
	$scope.ForwardPathCtrl=function(buttonName){
		if (buttonName=='ABCD')
		{
			$http({
				method: 'get',
				url: 'http://localhost:8080/SortCodeAccountNumber?sortCode=1500&accountNumber=1500&brand=RBS'
			}).then(function(response){
				 //alert("HTTP Request - Success");
				 $scope.valid=response.data;
				 alert($scope.valid);
				}, function(response){
					alert("HTTP Request - Error");
					alert('error: '+ response.status);
			});
			location.href="Redirect.html";
		}
		if (buttonName=='Next')
		{
			location.href="Redirect.html";
			window.history.forward();
		}
		if (buttonName=='Prev')
		{
			window.history.back();
		}
	};
});

app.controller("labelCtrl", function($scope, $http){
	$scope.name={};
	$http({
		method: 'get',
		url: 'http://localhost:9080/Prospect/WebContent/names.json'
	}).then(function(response){
		 //alert("HTTP Request - Success");
		 $scope.names=response.data;
		 //alert(typeof(response.data));
		}, function(response){
			alert("HTTP Request - Error");
			alert('error: '+ response.status);
	});
//	$scope.$watch(function(scope) {return scope.names},
//		function(){
//		   alert($scope.names);
//		   document.getElementById("myList").innerHTML=$scope.names;
//		}
//	);
});

app.controller("microCtrl", function($scope, $http){
	$scope.valid;
	$http({
		method: 'get',
		url: 'http://localhost:8080/SortCodeAccountNumber?sortCode=1500&accountNumber=1500&brand=RBS'
	}).then(function(response){
		 //alert("HTTP Request - Success");
		 $scope.valid=response.data;
		 alert($scope.valid);
		}, function(response){
			alert("HTTP Request - Error");
			alert('error: '+ response.status);
	});
//	$scope.$watch(function(scope) {return scope.names},
//		function(){
//		   alert($scope.names);
//		   document.getElementById("myList").innerHTML=$scope.names;
//		}
//	);
});

	