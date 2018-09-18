using UnityEngine;
using UnityEngine.SceneManagement;

public class GameController : MonoBehaviour {
    public void CheckoutScene(int sceneId) {
        SceneManager.LoadScene(sceneId);
    }
}
